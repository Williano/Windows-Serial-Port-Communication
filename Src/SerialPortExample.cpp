#define MAX_DATA_LENGTH 255
#define SEND

#include "SerialPort.h"
#include <iostream>


// Function prototypes
void autoConnect();
void sendDataToPort();
void readDataFromPort();

SerialPort* commPort;

const char* portNumber = "\\\\.\\COM3";
const char* data = "Test\n";

char receivedData[MAX_DATA_LENGTH];


int main()
{

	// Creates Serial Port instance and initialize with COM port
	commPort = new SerialPort(portNumber);

	autoConnect();

}



void autoConnect()
{
	while (1)
	{
		std::cout << "Searching in progress";

		while (!commPort->isConnected())
		{
			Sleep(100);
			std::cout << ".";
			commPort = new SerialPort(portNumber);
		}

		if (commPort->isConnected())
		{
			std::cout << std::endl << "Connection established at port" << portNumber << std::endl;
		}

#ifdef SEND
		while (commPort->isConnected())
		{
			sendDataToPort();
		}
#else
		while (commPort->isConnected())
		{
			readDataFromPort();
		}
#endif

	}
}


void sendDataToPort()
{
	unsigned int delayTime = 1000;

	commPort->writeSerialPort(data, MAX_DATA_LENGTH);
	Sleep(delayTime);
}


void readDataFromPort()
{
	int readData = commPort->readSerialPort(receivedData, MAX_DATA_LENGTH);
	printf("%s", receivedData);
	Sleep(10);
}
