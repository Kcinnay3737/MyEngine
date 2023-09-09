#pragma once

#include "Debug/Logger/ILogger.h"
#include "Debug/Logger/EnumLog.h"
#include <concrt.h>

namespace NPEngine
{
	class ConsoleLogger final : public ILogger
	{
	public:
		ConsoleLogger();
		~ConsoleLogger();

		void SetTextColor(ELogTextColor ForegourndColor, ELogTextColor BackgroundColor) override;

		void DebugMessage(const char* Message, ...) override;

		uint8_t MapToForegroundColor(ELogTextColor Color);
		uint8_t MapToBackgroundColor(ELogTextColor Color);

	private:
		HANDLE _HConsole;

	};
}