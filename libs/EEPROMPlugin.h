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


	char* read(uint16_t);//������ �� 0-��� ������ ������ ������ � ���������� ��������������� ���-�� ����
	void commit(); //���������� ���� _data � EEPROM, ������� � ������� ������, � � 0 - ����� ������ ������
	

public:
	bool init(); //�������������� ������ � ������� � ���������� true - ���� ��� ���-�� ����
	
	void _reset(); //���������� ��������� � ���������
	void printAllData(); //������� ���� _data � �������� �������
	void setData(const char*, SettTypesEnum);


	char* operator[](unsigned char); //��������������� ��������� ������� �� �������
};

extern EEPROMPluginClass EEPROMPlugin;

#endif