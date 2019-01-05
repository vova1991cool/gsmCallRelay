// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       gsmCallRelay.ino
    Created:	05.01.2019 00:21:01
    Author:     DESKTOP-ADQP0CT\vova1
*/
#include <avr\pgmspace.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "libs\SerialGSM.h"
#include "RelayToggler.h"

#define RELAY_PIN 5
#define GSM_BOOT_PIN 7
#define RESET_PIN 6
#define GSM_RX 3
#define GSM_TX 4
#define USER_NUMBERS = ["380957370982", "380965622167"]

void setup()
{
	pinMode(RELAY_PIN, OUTPUT);
	RelayToggler.init();

}

// Add the main program code into the continuous loop() function
void loop()
{
	RelayToggler.update();

}
