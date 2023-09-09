#pragma once

#include "Time/ITime.h"

namespace NPEngine
{
	class SDLTime final : public ITime
	{
	public:

	private:

	public:
		virtual ~SDLTime() = default;

		float GetDeltaTime() override;
		void SetFramePerSecond(int FramePerSecond) override;

	private:
		virtual void UpdateDeltaTime() override;
		virtual void UpdateLastFrameStartTime() override;
		virtual void UpdateCurrentFrameStartTime() override;
		virtual void ControlFrameRate() override;

	};
}