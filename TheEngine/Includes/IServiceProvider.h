#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IServiceProvider() = default;

	private:
		virtual bool Initialize(const Param& Params = Param{}) = 0;
		virtual void Shutdown(const Param& Params = Param{}) = 0;
	};
}