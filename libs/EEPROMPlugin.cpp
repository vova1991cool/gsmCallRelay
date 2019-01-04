// 
// 
// 

#include "EEPROMPlugin.h"

bool EEPROMPluginClass::init()
{
	if (EEPROM.read(0) != 0) {

		_setList = new char*[DATA_SIZE];

		for (size_t i = 0; i < DATA_SIZE; i++)
		{
			_setList[i] = read(DATA_IDS[i]);
		}
		return true;
	}

	return false;
}

#ifdef DEBUG
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif

void EEPROMPluginClass::commit()
{
#ifdef DEBUG
	Serial.println(freeRam());
#endif
	for (size_t i = 0, _len = strlen(_setList[i]) + 1; i < DATA_SIZE; i++, _len = strlen(_setList[i]) + 1) {
		uint16_t _currentBlock = DATA_IDS[i];
		EEPROM.write(_currentBlock, _len);
		for (size_t j = 0; j < _len; j++)
		{
			EEPROM.write(_currentBlock + j, _setList[i][j]);
		}
	}
}

char * EEPROMPluginClass::read(uint16_t _id)
{
	uint8_t _len = EEPROM.read(_id++);
	char* _data = new char[_len];
	for (uint8_t i = 0; i < _len; i++) {
		_data[i] = EEPROM.read(_id++);
	}
	return _data;
}

void EEPROMPluginClass::_reset()
{

	for (int i = 0; i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
	
	if (_setList != nullptr) delete _setList;

#ifdef DEBUG
	Serial.println(freeRam());
#endif

	_setList = new char*[DATA_SIZE];

	_setList[0] = "0965622167";
	_setList[1] = "mous12e";

	commit();
	delay(100);

}

void EEPROMPluginClass::printAllData()
{
	for (int i = 0; i <= DATA_SIZE; i++) {
		char* _data = read(DATA_IDS[i]);
		Serial.println(_data);
		delete _data;
	}
}

void EEPROMPluginClass::setData(const char *_data, SettTypesEnum type)
{
	delete _setList[type];
	_setList[type] = new char[strlen(_data) + 1];
	strcpy(_setList[type], _data);

	commit();
}

char* EEPROMPluginClass::operator[](unsigned char key)
{

	return _setList[key];
}


EEPROMPluginClass EEPROMPlugin;