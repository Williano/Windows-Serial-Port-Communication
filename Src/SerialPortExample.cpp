#define DATA_LENGTH 255

#include "SerialPort.h"
#include <iostream>


SerialPort* commPort;

const char* portNumber = "\\\\.\\COM4";
const char* data = "Test\n";

char receivedData[DATA_LENGTH];


int main()
{

	// Creates Serial Port instance and initialize with COM port
	commPort = new SerialPort(portNumber);

	std::cout << "Is connected: " << commPort->isConnected() << std::endl;


	// Sends data to COM port
	if (commPort->isConnected())
	{
		bool dataSent = commPort->writeSerialPort(data, DATA_LENGTH);

		if (dataSent)
		{
			std::cout << "Data Sent Successfully" << std::endl;

		}
		else
		{
			std::cerr << "Data sending failed" << std::endl;
		}
	}


	if (commPort->isConnected())
	{
		int dataReceived = commPort->readSerialPort(receivedData, DATA_LENGTH);

		if (dataReceived)
		{
			std::cout << receivedData << '\n';

		}
		else
		{
			std::cerr << "Error occured reading data" << "\n";
		}
	}
}
