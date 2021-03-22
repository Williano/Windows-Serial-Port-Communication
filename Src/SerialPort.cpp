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
			dcbSerialParameters.BaudRate = CBR_9600;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(this->m_handler, &dcbSerialParameters))
			{
				std::cout << "ALERT:: Coud not set serial port parameters\n";
			}
			else
			{

				this->m_isConnected = true;
				PurgeComm(this->m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(WAIT_TIME);
			}
		}
	}
}


SerialPort::~SerialPort()
{
	if (this->m_isConnected)
	{
		this->m_isConnected = false;
		CloseHandle(this->m_handler);
	}
}


int SerialPort::readSerialPort(const char* buffer, unsigned int buffer_size)
{
	DWORD bytesRead{};
	unsigned int toRead = 0;

	ClearCommError(this->m_handler, &this->m_erros, &this->m_status);

	if (this->m_status.cbInQue > 0)
	{
		if (this->m_status.cbInQue > buffer_size)
		{
			toRead = buffer_size;
		}
		else
		{
			toRead = this->m_status.cbInQue;
		}
	}

	memset((void*)buffer, 0, buffer_size);

	if (ReadFile(this->m_handler, (void*)buffer, toRead, &bytesRead, NULL))
	{
		return bytesRead;
	}

	return 0;
}


bool SerialPort::writeSerialPort(const char* buffer, unsigned int bufferSize)
{
	DWORD bytesSend;

	if (!WriteFile(this->m_handler, (void*)buffer, bufferSize, &bytesSend, 0))
	{
		ClearCommError(this->m_handler, &this->m_erros, &this->m_status);
		return false;
	}

	return true;
}


bool SerialPort::isConnected()
{
	if (!ClearCommError(this->m_handler, &this->m_erros, &this->m_status))
	{
		this->m_isConnected = false;
	}

	return this->m_isConnected;
}


void SerialPort::closeSerial()
{
	CloseHandle(this->m_handler);
}
