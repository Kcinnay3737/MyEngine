#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class IWorldProvider : public IServiceProvider
	{
		friend class Engine;
	public:
		virtual ~IWorldProvider() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void StartFrame() = 0;

		virtual void Update(float DeltaTime) = 0;
		virtual void PostUpdate() = 0;

		virtual void Render() = 0;
		virtual void PostRender() = 0;

		virtual void EndFrame() = 0;
	};
}