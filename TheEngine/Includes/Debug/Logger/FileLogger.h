#pragma once

#include "Debug/Logger/ILogger.h"
#include <fstream>

namespace NPEngine
{
	class FileLogger final : public ILogger
	{
	public:
		FileLogger();
		~FileLogger();

		void DebugMessage(const char* Message, ...) override;

	private:
		std::ofstream _File;
	};
}