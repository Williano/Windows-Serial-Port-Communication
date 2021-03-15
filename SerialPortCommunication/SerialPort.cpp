#include "SerialPort.h"


SerialPort::SerialPort(const char* portName) {

	this->m_isConnected = false;
	this->m_handler = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (this->m_handler == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			std::cerr << "ERROR: Handle was not attached. Reason: " << portName << " not available\n";
		}
		else
		{
			std::cerr << "ERROR!!!\n";
		}
	}
	else
	{
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->m_handler, &dcbSerialParameters))
		{
			std::cerr << "Failed to get current serial parameters\n";
		}
		else
		{
			this->m_isConnected = true;
			PurgeComm(this->m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
			Sleep(WAIT_TIME);
		}
	}
}
