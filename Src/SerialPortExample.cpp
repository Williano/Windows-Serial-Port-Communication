#define DATA_LENGTH 255

#include "SerialPort.h"
#include <iostream>


//SerialPort* commPort;
//
//const char* portNumber = "\\\\.\\COM6";
//const char* data = "Test\n";
//
//char receivedData[DATA_LENGTH];
//
//
//int main()
//{
//
//	// Creates Serial Port instance and initialize with COM port
//	commPort = new SerialPort(portNumber);
//
//	std::cout << "Is connected: " << commPort->isConnected() << std::endl;
//
//
//	// Sends data to COM port
//	//if (commPort->isConnected())
//	//{
//	//	while (commPort->isConnected())
//	//	{
//	//		bool dataSent = commPort->writeSerialPort(data, DATA_LENGTH);
//
//	//		if (dataSent)
//	//		{
//	//			std::cout << "Data Sent Successfully" << std::endl;
//
//	//		}
//	//		else
//	//		{
//	//			std::cerr << "Data sending failed" << std::endl;
//	//		}
//	//	}
//	//}
//
//
//	 // Recieves data from COM port
//	if (commPort->isConnected())
//	{
//		int dataReceived = commPort->readSerialPort(receivedData, DATA_LENGTH);
//
//		if (dataReceived)
//		{
//			std::cout << "1";
//			std::cout << receivedData << '\n';
//
//		}
//		else
//		{
//			std::cerr << "Error occured reading data" << "\n";
//		}
//	}
//
//	return 0;
//}

//
//int main()
//{
//	SerialPort port("COM6", 9600);
//
//	while (1)
//	{
//		unsigned char dataReceived;
//		port.recieveData(dataReceived, 1);
//
//		std::cout << dataReceived << std::endl;
//	}
//
//	return 0;
//}




/* Verison 3 */

const char* portName = "\\\\.\\COM3";

//Declare a global object
SerialPort* arduino;

//Here '\n' is a delimiter 
const char* sendString = "Hello World\n";


//char receivedString[DATA_LENGTH];

int main(void)
{
	arduino = new SerialPort(portName);

	// Sending data
	if (arduino->isConnected())
	{
		while (arduino->isConnected())
		{
			bool hasWritten = arduino->writeSerialPort(sendString, DATA_LENGTH);
			if (hasWritten)
			{
				std::cout << "Data Written Successfully" << std::endl;
			}
			else
			{
				std::cerr << "Data was not written" << std::endl;
			}
		}
	}


	// Receiving data
	//if (arduino->isconnected()) {
	//	int hasread = arduino->readserialport(receivedstring, data_length);
	//	if (hasread) std::cout << receivedstring << "\n";
	//	else std::cerr << "error occured reading data" << "\n";
	//}
}
