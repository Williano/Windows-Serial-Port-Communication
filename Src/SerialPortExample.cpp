#define DATA_LENGTH 255

#include "SerialPort.h"
#include <iostream>


// Function prototypes
void autoConnect();
void sendDataToPort();
void readDataFromPort();

SerialPort* commPort;

const char* portNumber = "\\\\.\\COM6";
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
		while (commPort->isConnected())
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
	}


	// Recieves data from COM port
	//if (commPort->isConnected())
	//{
	//	int dataReceived = commPort->readSerialPort(receivedData, DATA_LENGTH);

	//	if (dataReceived)
	//	{
	//		std::cout << receivedData << '\n';

	//	}
	//	else
	//	{
	//		std::cerr << "Error occured reading data" << "\n";
	//	}
	//}
}



void autoConnect()
{
	while (1)
	{
		std::cout << "Searching i progress";

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
	}
}


void sendDataToPort()
{}


void readDataFromPort()
{}
