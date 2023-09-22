#pragma once

#include "Debug/Logger/ILogger.h"
#include <fstream>

namespace NPEngine
{
	class FileLogger final : public ILogger
	{
	private:
		std::ofstream _File;

	public:
		~FileLogger() = default;

		void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) { };

		void LogMessage(const char* Message, ...) override;

	private:
		virtual bool Initialize() override;
		virtual void Shutdown() override;
	};
}