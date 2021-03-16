#include "SerialPort.h"
#include <iostream>


const char* portNumber = "\\\\.\\COM2";

SerialPort* commPort;


int main()
{
	commPort = new SerialPort(portNumber);

	std::cout << "Is connected: " << commPort->isConnected() << std::endl;
}
