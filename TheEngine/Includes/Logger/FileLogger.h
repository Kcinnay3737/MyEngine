#pragma once

#include "Logger/ILogger.h"
#include <fstream>

namespace NPEngine
{
	class FileLogger final : public ILogger
	{
	private:
		std::ofstream _File;

	public:
		virtual ~FileLogger() = default;

		void SetTextColor(EColor ForegourndColor = EColor::White, EColor BackgroundColor = EColor::Black) { };

		void LogMessage(const char* Message, ...) override;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;
	};
}