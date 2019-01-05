// SerialGSM version 1.1
// by Meir Michanie
// meirm@riunx.com
// error codes
// http://www.developershome.com/sms/resultCodes2.asp
#include "SerialGSM.h"

void SerialGSM::FwdSMS2Serial(){
  Serial.println(F("AT+CLIP=1"));
  this->println(F("AT+CLIP=1"));
  delay(200);
  Serial.println(F("AT+CMGF=1")); // set SMS mode to text
  this->println(F("AT+CMGF=1")); // set SMS mode to text
  delay(200);
  this->ReadLine();
  Serial.println(F("AT+CNMI=2,2,0,0,0")); // set module to send SMS data to serial out upon receipt 
  this->println(F("AT+CNMI=2,2,0,0,0")); // set module to send SMS data to serial out upon receipt 
  delay(200);
  this->ReadLine();
}

void SerialGSM::answer(){
  this->println(F("ATA"));
}

void SerialGSM::hungup(){
  this->println(F("ATH"));
}

void SerialGSM::dial(const char * pnumber){
	Serial.println(pnumber);
  this->Rcpt(pnumber);
  this->print(F("ATD"));
  this->print(pnumber);
  this->println(F(";"));
  //this->println('\r');
}

void SerialGSM::SendSMS(const char * cellnumber,const char * outmsg){
  this->Rcpt(cellnumber);
  if (verbose) Serial.println(rcpt);
  this->StartSMS();
//  outmessage = outmsg;
  Serial.print(outmsg);
  this->print(outmsg);
  this->EndSMS();
  delay(1000);
  this->ReadLine();
}

void SerialGSM::SendSMS(const char * outmsg)
{
	SendSMS(sendernumber, outmsg);
}
/*
void SerialGSM::SendSMS(){
  if (verbose) Serial.println(rcpt);
  if (verbose) Serial.println(outmessage);
  this->StartSMS();
  Serial.print(outmessage);
  this->print(outmessage);
  this->EndSMS();
  delay(500);
  this->ReadLine();
}
*/
void SerialGSM::DeleteAllSMS(){
  Serial.println(F("AT+CMGD=1,4")); // delete all SMS
  this->println(F("AT+CMGD=1,4")); // delete all SMS
//  Serial.println("AT+CMGDA=\"DEL ALL\"");
//  this->println("AT+CMGDA=\"DEL ALL\"");
  delay(200);
  this->ReadLine();
}

void SerialGSM::getBallance()
{
	this->println(F("ATD*111#"));
	delay(200);
	this->ReadLine();
}

void SerialGSM::Reset(){
  Serial.println(F("AT+CFUN=1,1")); // Reset Modem
  this->println(F("AT+CFUN=1,1")); // Reset Modem
  delay(200);
  this->ReadLine();
}

void SerialGSM::PowrDwn()
{
	Serial.println(F("AT+CPOWD=0"));
	this->println(F("AT+CPOWD=0"));
	delay(200);
	this->ReadLine();
}


void SerialGSM::EndSMS(){
  this->print(char(26));  // ASCII equivalent of Ctrl-Z
  Serial.print(F("\n"));

  //delay(5 * 1000); // the SMS module needs time to return to OK status
}

void SerialGSM::StartSMS(){

  Serial.println(F("AT+CMGF=1")); // set SMS mode to text
  this->println(F("AT+CMGF=1")); // set SMS mode to text
  delay(200);
  this->ReadLine();

  Serial.print(F("AT+CMGS="));
  this->print(F("AT+CMGS="));
  
  this->print(char(34)); // ASCII equivalent of "

  Serial.print(rcpt);
  this->print(rcpt);

  this->println(char(34));  // ASCII equivalent of "

  delay(500); // give the module some thinking time
  this->ReadLine();

}

bool SerialGSM::ReadLine(){
  static int pos=0;
  char nc;
  while (this->available()){
    nc=this->read();
    if ((nc == '\n')||(pos > DATA_CONSTANTS[1])||((millis()> lastrec + DATA_CONSTANTS[0])&&(pos > 0))){
      nc='\0';
      lastrec=millis();
      inmessage[pos]=nc;
     pos=0;
	 if (verbose) { Serial.print(inmessage); Serial.print("\n"); }
      return true;
    }
    else if (nc=='\r') {
    }
    else{
      inmessage[pos++]=nc;
      lastrec=millis();
    }
  }
  return false;
}


bool SerialGSM::ReceiveSMS(){

  static boolean insms=0;
  if (this->ReadLine()){
  // Get the number of the sms sender in order to be able to reply


	if ( (strstr_PF(inmessage, F("CMT: ")) != NULL) || (strstr_PF(inmessage, F("CUSD: ")) != NULL) ){
	    insms=1;
	    int sf=6;
		if (strstr_PF(inmessage, F("CUSD: ")) != NULL) sf = 7;
	    if(strstr_PF(inmessage, F("+CMT: ")) || strstr_PF(inmessage, F("+CUSD: "))) sf++;
		if (strstr_PF(inmessage, F("CMT: "))) {
			for (int i = 0; i < PHONESIZE; i++) {
				sendernumber[i] = inmessage[sf + i];
			}
			sendernumber[PHONESIZE] = '\0';
		}
	//	else if (strstr(inmessage, "CUSD: ")) {
		//	Serial.println(inmessage);
	//		sf += 2;
	//		byte i = 0;
	//		outmessage = new char[30];
	//		do{
	//			outmessage[i] = inmessage[sf + i];
	//		}while (inmessage[sf + i++] != 'n');
	//		outmessage[i++] = '.';
	//		outmessage[i] = '\0';
	//		this->Rcpt(sendernumber);
	//		this->SendSMS();
	//		delete outmessage;
	//	}
		return false;
	 }else{ 
		if(insms) {
			insms=0;
			return true;
		}
	}
  }
  return false;
  
}


boolean SerialGSM::Verbose(){
	return verbose;
}

void SerialGSM::Verbose(boolean var1){
	verbose=var1;
}

char * SerialGSM::Sender(){
	return sendernumber;
}


char * SerialGSM::Rcpt(){
	return rcpt;
}

char * SerialGSM::Message(){
	return inmessage;
}


void SerialGSM::Sender(char * var1){
	sprintf(sendernumber,"%s",var1);
}


void SerialGSM::Rcpt(const char * var1){
	sprintf(rcpt,"%s",var1);
}
/*
void SerialGSM::Message(char * var1){
	sprintf(outmessage,"%s",var1);
}
*/
void SerialGSM::Boot(uint8_t pow_pin){
  int counter=0;
//  Serial.println(pow_pin);
//  delay(1000);
  pinMode(pow_pin, OUTPUT);
  digitalWrite(pow_pin, LOW);
  delay(1000);
  digitalWrite(pow_pin, HIGH);
  delay(1000);
  digitalWrite(pow_pin, LOW);
  while(counter++ < DATA_CONSTANTS[2]){
    if (verbose) Serial.print(".");
    delay(1000);
  }
  if (verbose) Serial.println();
  
}
