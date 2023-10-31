#pragma once

#include "Logger/ILogger.h"
#include <concrt.h>

namespace NPEngine
{
	class ConsoleLogger final : public ILogger
	{
	private:
		HANDLE _HConsole = HANDLE();

	public:
		virtual ~ConsoleLogger() = default;

		void SetTextColor(EColor ForegourndColor, EColor BackgroundColor) override;

		void LogMessage(const char* Message, ...) override;

		uint8_t MapToForegroundColor(EColor Color);
		uint8_t MapToBackgroundColor(EColor Color);

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

	};
}