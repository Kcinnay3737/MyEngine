#pragma once

#include "Graphics/Color.h"

namespace NPEngine
{
	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		virtual void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) = 0;
		
		virtual void DebugMessage(const char* Message, ...) = 0;

	private:
		friend class Engine;
		virtual bool Initialize() = 0;
		friend class Engine;
		virtual void Shutdown() = 0;
	};
}