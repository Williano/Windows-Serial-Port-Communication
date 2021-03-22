#include "SerialPort.h"

//
//SerialPort::SerialPort(const char* portName) {
//
//	this->m_isConnected = false;
//	this->m_handler = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (this->m_handler == INVALID_HANDLE_VALUE)
//	{
//		if (GetLastError() == ERROR_FILE_NOT_FOUND)
//		{
//			std::cerr << "ERROR: Handle was not attached. Reason: " << portName << " not available\n";
//		}
//		else
//		{
//			std::cerr << "ERROR!!!\n";
//		}
//	}
//	else
//	{
//		DCB dcbSerialParameters = { 0 };
//
//		if (!GetCommState(this->m_handler, &dcbSerialParameters))
//		{
//			std::cerr << "Failed to get current serial parameters\n";
//		}
//		else
//		{
//			this->m_isConnected = true;
//			PurgeComm(this->m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
//			Sleep(WAIT_TIME);
//		}
//	}
//}
//
//
//SerialPort::~SerialPort()
//{
//	if (this->m_isConnected)
//	{
//		this->m_isConnected = false;
//		CloseHandle(this->m_handler);
//	}
//}
//
//
//int SerialPort::readSerialPort(const char* buffer, unsigned int buffer_size)
//{
//	DWORD bytesRead{};
//	unsigned int toRead = 0;
//
//	ClearCommError(this->m_handler, &this->m_erros, &this->m_status);
//
//	if (this->m_status.cbInQue > 0)
//	{
//		if (this->m_status.cbInQue > buffer_size)
//		{
//			toRead = buffer_size;
//		}
//		else
//		{
//			toRead = this->m_status.cbInQue;
//		}
//	}
//
//	memset((void*)buffer, 0, buffer_size);
//
//	if (ReadFile(this->m_handler, (void*)buffer, toRead, &bytesRead, NULL))
//	{
//		return bytesRead;
//	}
//
//	return 0;
//}
//
//
//bool SerialPort::writeSerialPort(const char* buffer, unsigned int bufferSize)
//{
//	DWORD bytesSend;
//
//	if (!WriteFile(this->m_handler, (void*)buffer, bufferSize, &bytesSend, 0))
//	{
//		ClearCommError(this->m_handler, &this->m_erros, &this->m_status);
//		return false;
//	}
//
//	return true;
//}
//
//
//bool SerialPort::isConnected()
//{
//	if (!ClearCommError(this->m_handler, &this->m_erros, &this->m_status))
//	{
//		this->m_isConnected = false;
//	}
//
//	return this->m_isConnected;
//}
//
//
//void SerialPort::closeSerial()
//{
//	CloseHandle(this->m_handler);
//}


/* Constructors */
SerialPort::SerialPort() : m_isConnected(false) {}

SerialPort::SerialPort(const char* port, unsigned long baudRate) : m_isConnected(false)
{
	initialize(port, baudRate);
}


/* Initialization */
void SerialPort::initialize(const char* port, unsigned long baudRate)
{
	wchar_t wcPort[64];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcPort, strlen(port), port, _TRUNCATE);

	m_handler = CreateFile(wcPort, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (m_handler == INVALID_HANDLE_VALUE)
	{
		std::cout << "ERROR!::Error during opening port" << port << std::endl;
		return;
	}

	DCB serialParameters;
	if (!GetCommState(m_handler, &serialParameters))
	{
		std::cout << "ERROR!:: Failed to get current serial parameters" << std::endl;
		return;
	}

	serialParameters.DCBlength = sizeof(DCB);
	serialParameters.BaudRate = baudRate;
	serialParameters.StopBits = ONESTOPBIT;
	serialParameters.Parity = NOPARITY;

	if (!SetCommState(m_handler, &serialParameters))
	{
		std::cout << "ALERT!:: Failed to set the Serial Port Parameters" << std::endl;
		return;
	}

	m_isConnected = true;
	PurgeComm(m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
}


/* Serial Input and Output*/
void SerialPort::recieveData(unsigned char& data, unsigned int byteSize)
{
	ReadFile(m_handler, &data, byteSize, NULL, NULL);
}


void SerialPort::transmitData(unsigned char* data, unsigned int byteSize)
{
	WriteFile(m_handler, data, byteSize, NULL, NULL);
}


/* State */
void SerialPort::connect()
{
	m_isConnected = true;
}


void SerialPort::disConnect()
{
	m_isConnected = false;
}


bool SerialPort::isConnected()
{
	return m_isConnected;
}


SerialPort::~SerialPort()
{
	if (m_isConnected)
	{
		m_isConnected = false;
		CloseHandle(m_handler);
	}
}
