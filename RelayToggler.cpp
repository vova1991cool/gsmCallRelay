// 
// 
// 

#include "RelayToggler.h"

void RelayTogglerClass::init()
{
	_gsm_module = new SerialGSM(GSM_RX, GSM_TX);
	_gsm_module->begin(9600);
	_gsm_module->Verbose(true);
	_gsm_module->FwdSMS2Serial();
	_gsm_module->PowrDwn();
	_gsm_module->Boot(GSM_BOOT_PIN);
	_gsm_module->begin(9600);
	_gsm_module->Verbose(true);
	_gsm_module->FwdSMS2Serial();
	_gsm_module->DeleteAllSMS();

}

void RelayTogglerClass::update()
{

}


RelayTogglerClass RelayToggler;

