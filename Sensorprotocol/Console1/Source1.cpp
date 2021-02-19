/*
 The MySensors library adds a new layer on top of the RF24 library.
 It handles radio network routing, relaying and ids.


 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "MyMessage.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __Raspberry_Pi
#define min(a,b) (a<b?a:b)

char* itoa(int value, char* result, int base);
char* ltoa(long value, char* result, int base);
char* dtostrf(float f, int width, int decimals, char* result);
char* utoa(unsigned int num, char* str, int radix);
char* ultoa(unsigned long num, char* str, int radix);
#endif

MyMessage::MyMessage() {
	destination = 0; // Gateway is default destination
}

MyMessage::MyMessage(uint8_t _sensor, uint8_t _type) {
	destination = 0; // Gateway is default destination
	sensor = _sensor;
	type = _type;
}

bool MyMessage::isAck() const {
	return miGetAck();
}

/* Getters for payload converted to desired form */
void* MyMessage::getCustom() const {
	return (void*)data;
}

const char* MyMessage::getString() const {
	uint8_t payloadType = miGetPayloadType();
	if (payloadType == P_STRING) {
		return data;
	}
	else {
		return NULL;
	}
}