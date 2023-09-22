#include "Debug/Logger/FileLogger.h"
#include <iostream>
#include <stdarg.h>

using namespace NPEngine;

bool FileLogger::Initialize()
{
	_File.open("LogFile.txt", std::ios::out | std::ios::trunc);

	return true;
}

void FileLogger::Shutdown()
{
	if (_File.is_open())
	{
		_File.close();
	}
}

void FileLogger::LogMessage(const char* Message, ...)
{
	if (_File.is_open()) 
	{
		va_list Args;
		va_start(Args, Message);

		int BufferSize = vsnprintf(nullptr, 0, Message, Args) + 1;
		va_end(Args);

		char* Buffer = new char[BufferSize];

		va_start(Args, Message);
		vsnprintf(Buffer, BufferSize, Message, Args);
		va_end(Args);

		_File << Buffer << std::endl;

		delete[] Buffer;
	}
}