#include "MySensor.h"

using namespace std;

#ifdef __Raspberry_Pi
#include <PiEEPROM.h>
#include "RF24.h"
#include "RF24_config.h"
#else
#include "utility/LowPower.h"
#include "utility/RF24.h"
#include "utility/RF24_config.h"
#endif


// Inline function and macros
inline MyMessage& build(MyMessage& msg, uint8_t sender, uint8_t destination, uint8_t sensor, uint8_t command, uint8_t type, bool enableAck) {
	msg.sender = sender;
	msg.destination = destination;
	msg.sensor = sensor;
	msg.type = type;
	mSetCommand(msg, command);
	mSetRequestAck(msg, enableAck);
	mSetAck(msg, false);
	return msg;
}

#ifdef __Raspberry_Pi
MySensor::MySensor(uint8_t _cepin, uint8_t _cspin, uint32_t spispeed) : RF24(_cepin, _cspin, spispeed) {
	timeval curTime;
	gettimeofday(&curTime, NULL);
	millis_at_start = curTime.tv_sec;
}
#else
MySensor::MySensor(uint8_t _cepin, uint8_t _cspin) : RF24(_cepin, _cspin) {
}
#endif

void MySensor::begin(void (*_msgCallback)(const MyMessage&), uint8_t _nodeId, boolean _repeaterMode, uint8_t _parentNodeId, rf24_pa_dbm_e paLevel, uint8_t channel, rf24_datarate_e dataRate) {
#ifndef __Raspberry_Pi
	Serial.begin(BAUD_RATE);
#endif
	isGateway = false;
	repeaterMode = _repeaterMode;
	msgCallback = _msgCallback;

	if (repeaterMode) {
		setupRepeaterMode();
	}
	setupRadio(paLevel, channel, dataRate);

	// Read settings from EEPROM
	eeprom_read_block((void*)&nc, (void*)EEPROM_NODE_ID_ADDRESS, sizeof(NodeConfig));
	// Read latest received controller configuration from EEPROM
	eeprom_read_block((void*)&cc, (void*)EEPROM_CONTROLLER_CONFIG_ADDRESS, sizeof(ControllerConfig));
	if (cc.isMetric == 0xff) {
		// EEPROM empty, set default to metric
		cc.isMetric = 0x01;
	}

	if (_parentNodeId != AUTO) {
		if (_parentNodeId != nc.parentNodeId) {
			nc.parentNodeId = _parentNodeId;
			// Save static parent id in EEPROM
			eeprom_write_byte((uint8_t*)EEPROM_PARENT_NODE_ID_ADDRESS, _parentNodeId);
		}
		autoFindParent = false;
	}
	else {
		autoFindParent = true;
	}

	if ((_nodeId != AUTO) && (nc.nodeId != _nodeId)) {
		// Set static id
		nc.nodeId = _nodeId;
		// Save static id in EEPROM
		eeprom_write_byte((uint8_t*)EEPROM_NODE_ID_ADDRESS, _nodeId);
	}

	// If no parent was found in EEPROM. Try to find one.
	if (autoFindParent && nc.parentNodeId == 0xff) {
		findParentNode();
	}

	// Try to fetch node-id from gateway
	if (nc.nodeId == AUTO) {
		requestNodeId();
	}

	debug(PSTR("%s started, id %d\n"), repeaterMode ? "repeater" : "sensor", nc.nodeId);
