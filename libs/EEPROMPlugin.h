// EEPROMPlugin.h

#ifndef _EEPROMPLUGIN_h
#define _EEPROMPLUGIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EEPROM.h"

#define DEBUG

#ifdef DEBUG
int freeRam();
#endif

enum SettTypesEnum
{
	PHONE_NUMBERS,
	PASSWORD
};

class EEPROMPluginClass
{
private:
	const uint16_t DATA_IDS[2] = { 0, 250 };
	const size_t DATA_SIZE = 2;

	char **_setList;


	char* read(uint16_t);//читает из 0-ого адреса длинну записи и возвращает соответствующее кол-во байт
	void commit(); //записывает поле _data в EEPROM, начиная с первого адреса, а в 0 - пишет длинну записи
	

public:
	bool init(); //инициализирует работу с памятью и возвращает true - если там что-то есть
	
	void _reset(); //Сбрасывает настройки к заводским
	void printAllData(); //Выводит поле _data в серийный монитор
	void setData(const char*, SettTypesEnum);


	char* operator[](unsigned char); //Переопределение оператора доступа по индексу
};

extern EEPROMPluginClass EEPROMPlugin;

#endif