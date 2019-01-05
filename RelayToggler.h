// RelayToggler.h

#ifndef _RELAYTOGGLER_h
#define _RELAYTOGGLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class RelayTogglerClass
{
 private:
	 SerialGSM *_gsm_module;

 public:
	void init();
	void update();
};

extern RelayTogglerClass RelayToggler;

#endif

