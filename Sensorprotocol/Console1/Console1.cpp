#endif

// Start up the radio library
setupRadio(paLevel, channel, dataRate);
try {
	setupRadio(paLevel, channel, dataRate);
}
catch (const char* msg) {
	printf("Unable to start up the radio library. (Error: %s)\n", msg);
	exit(EXIT_FAILURE);
}
RF24::openReadingPipe(WRITE_PIPE, BASE_RADIO_ID);
RF24::openReadingPipe(CURRENT_NODE_PIPE, BASE_RADIO_ID);
RF24::startListening();
@@ - 237, 20 + 242, 25 @@ void MyGateway::setInclusionMode(boolean newMode) {
}

void MyGateway::processRadioMessage() {
	if (process()) {
		// A new message was received from one of the sensors
		MyMessage message = getLastMessage();
		if (mGetCommand(message) == C_PRESENTATION && inclusionMode) {
			rxBlink(3);
		}
		else {
			rxBlink(1);
		}
		// Pass along the message from sensors to serial line
		serial(message);
	}
	try {
		if (process()) {
			// A new message was received from one of the sensors
			MyMessage message = getLastMessage();
			if (mGetCommand(message) == C_PRESENTATION && inclusionMode) {
				rxBlink(3);
			}
			else {
				rxBlink(1);
			}
			// Pass along the message from sensors to serial line
			serial(message);
		}
	}
	catch (const char* msg) {
		printf("Unable to process radio messages. (Error: %s)\n", msg);
		exit(EXIT_FAILURE);
	}

	checkButtonTriggeredInclusion();
	checkInclusionFinished();
	checkButtonTriggeredInclusion();
	checkInclusionFinished();
}

void MyGateway::serial(const char* fmt, ...) {
	@@ - 319, 4 + 329, 3 @@ void MyGateway::errBlink(uint8_t cnt) {
		if (countErr == 255) { countErr = cnt; }
#endif
	}