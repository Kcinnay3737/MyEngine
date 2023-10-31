#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class ILoggerProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~ILoggerProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) = 0;
		virtual void Shutdown(const Param& Params) = 0;
	};
}