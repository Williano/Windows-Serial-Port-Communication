#pragma once


//#define WAIT_TIME 2000
//#define MAX_DATA_LENGTH
//
//#include <Windows.h>
//#include <iostream>
//
//
//class SerialPort
//{
//
//private:
//
//	HANDLE m_handler;
//	bool m_isConnected;
//	COMSTAT m_status;
//	DWORD m_erros;
//
//public:
//
//	explicit SerialPort(const char* portName);
//	~SerialPort();
//
//
//
//	// Reads bytes from serial port to buffer, returns read bytes count, or if error occurs, returns 0
//	int readSerialPort(const char* buffer, unsigned int bufferSize);
//
//
//	// Sends provided buffer to serial port, returns true if succeed, false if not.
//	bool writeSerialPort(const char* buffer, unsigned int bufferSize);
//
//
//	// Checks if serial port is connected.
//	bool isConnected();
//
//	// Close port 
//	void closeSerial();
//};


#include <Windows.h>
#include <iostream>


class SerialPort
{
private:
	HANDLE m_handler;
	bool m_isConnected;


public:

	// Constructors
	SerialPort();
	SerialPort(const char* port, unsigned long baudRate);


	// Initialization
	void initialize(const char* port, unsigned long baudRate);


	// Serial Input and Output
	void recieveData(unsigned char& data, unsigned int byteSize);
	void transmitData(unsigned char* data, unsigned int byteSize);


	// Connection State
	void connect();
	void disConnect();
	bool isConnected();


	// Destructor
	~SerialPort();
};
