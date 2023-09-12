#pragma once

#include "EnumLog.h"

namespace NPEngine
{
	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		virtual void SetTextColor(ELogTextColor ForegourndColor = ELogTextColor::White, ELogTextColor BackgroundColor = ELogTextColor::Black) = 0;
		
		virtual void DebugMessage(const char* Message, ...) = 0;

	private:
	};
}