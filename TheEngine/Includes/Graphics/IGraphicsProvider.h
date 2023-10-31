#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class IGraphicsProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IGraphicsProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void Clear() = 0;
		virtual void Present() = 0;
	};
}