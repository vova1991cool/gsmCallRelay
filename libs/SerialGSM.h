#ifndef _SerialGSM_H
#define _SerialGSM_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "SoftwareSerial.h"

const uint16_t DATA_CONSTANTS[] = { 2000, 200, 6 };

#define PHONESIZE 13

class SerialGSM : public SoftwareSerial {
public:
	SerialGSM(unsigned char rxpin, unsigned char txpin)
		:SoftwareSerial(rxpin, txpin), verbose(false) {}
  void FwdSMS2Serial();
//  void SendSMS();
  void SendSMS(const char * cellnumber,const char * outmsg);
  void SendSMS(const char* outmsg);
  void DeleteAllSMS();
  void getBallance();
  void Reset();
  void PowrDwn();
  void answer();
  void hungup();
  void dial(const char * pnumber);
  void EndSMS();
  void StartSMS();
  bool ReadLine();
  bool ReceiveSMS();
  void Verbose(boolean var1);
  boolean Verbose();
  void Sender(char * var1);
  char * Sender();
  void Rcpt(const char * var1);
  char * Rcpt();
//  void Message(char * var1);
  char * Message();
  void Boot(uint8_t pow_pin);

  boolean verbose;
  char sendernumber[PHONESIZE + 1];
  char rcpt[PHONESIZE + 1];
//  char* outmessage;
  char inmessage[50];
  
protected:
  unsigned long lastrec;
  
};

#endif /* not defined _SerialGSM_H */

