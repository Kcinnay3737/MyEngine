#pragma once

#include "Logger/ILoggerProvider.h"
#include "Graphics/Color.h"

namespace NPEngine
{
	class ILogger : public ILoggerProvider
	{
	public:
		virtual ~ILogger() = default;

		virtual void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) = 0;
		
		virtual void LogMessage(const char* Message, ...) = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;
	};
}