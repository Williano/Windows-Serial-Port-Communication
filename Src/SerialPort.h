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



	// Reading bytes from serial port to buffer, returns read bytes count, or if error occurs, returns 0
	int readSerialPort(const char* buffer, unsigned int bufferSize);


	// Sending provided buffer to serial port, returns true if succeed, false if not.
	bool writeSerialPort(const char* buffer, unsigned int bufferSize);


	bool isConnected();


	void closeSerial();
};
