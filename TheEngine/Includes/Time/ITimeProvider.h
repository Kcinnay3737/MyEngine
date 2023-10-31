#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class ITimeProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~ITimeProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) = 0;
		virtual void Shutdown(const Param& Params) = 0;

		virtual void InitialiseTime() = 0;
		virtual void OnStartFrame() = 0;
		virtual void OnEndFrame() = 0;
	};
}