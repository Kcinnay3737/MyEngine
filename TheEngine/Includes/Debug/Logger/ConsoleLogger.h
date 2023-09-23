#pragma once

#include "Debug/Logger/ILogger.h"
#include <concrt.h>

namespace NPEngine
{
	class ConsoleLogger final : public ILogger
	{
	private:
		HANDLE _HConsole = HANDLE();

	public:
		~ConsoleLogger() = default;

		void SetTextColor(EColor ForegourndColor, EColor BackgroundColor) override;

		void LogMessage(const char* Message, ...) override;

		uint8_t MapToForegroundColor(EColor Color);
		uint8_t MapToBackgroundColor(EColor Color);

	private:
		virtual bool Initialize() override;
		virtual void Shutdown() override;

	};
}