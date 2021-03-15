#pragma once


#define WAIT_TIME 2000
#define MAX_DATA_LENGTH

#include <Windows.h>
#include <iostream>


class SerialPort
{

private:

	HANDLE m_handler;
	bool m_isConnected;
	COMSTAT m_status;
	DWORD m_erros;

public:

	explicit SerialPort(const char* portName);
	~SerialPort();

	int readSerialPort(const char* buffer, unsigned int bufferSize);
	bool writeSerialPort(const char* buffer, unsigned int bufferSize);
	bool isConnected();
	void closeSerial();
};
