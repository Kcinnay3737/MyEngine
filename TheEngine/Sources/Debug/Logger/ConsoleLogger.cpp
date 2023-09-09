#include "Debug/Logger/ConsoleLogger.h"
#include <windows.h>
#include <stdio.h>
#include <consoleapi.h>
#include <iostream>

using namespace NPEngine;

ConsoleLogger::ConsoleLogger()
{
	AllocConsole();

	int R = freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

	_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

ConsoleLogger::~ConsoleLogger()
{
	FreeConsole();
}

void ConsoleLogger::DebugMessage(const char* Message, ...)
{
	va_list Args;
	va_start(Args, Message);
	vprintf(Message, Args);
	va_end(Args);
	printf("\n");
}

void ConsoleLogger::SetTextColor(ELogTextColor ForegourndColor, ELogTextColor BackgroundColor)
{
	SetConsoleTextAttribute(_HConsole, MapToForegroundColor(ForegourndColor) | MapToBackgroundColor(BackgroundColor));
}

uint8_t ConsoleLogger::MapToForegroundColor(ELogTextColor Color)
{
	switch (Color)
	{
	case ELogTextColor::White: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	case ELogTextColor::Black: return 0;
	case ELogTextColor::Blue: return FOREGROUND_BLUE;
	case ELogTextColor::Green: return FOREGROUND_GREEN;
	case ELogTextColor::Red: return FOREGROUND_RED;
	default: return 0;
	}
}

uint8_t ConsoleLogger::MapToBackgroundColor(ELogTextColor Color)
{
	switch (Color)
	{
	case ELogTextColor::White: return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	case ELogTextColor::Black: return 0;
	case ELogTextColor::Blue: return BACKGROUND_BLUE;
	case ELogTextColor::Green: return BACKGROUND_GREEN;
	case ELogTextColor::Red: return BACKGROUND_RED;
	default: return 0;
	}
}
