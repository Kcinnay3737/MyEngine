#pragma once

#include "Time/ITimeProvider.h"

namespace NPEngine
{
	class ITime : public ITimeProvider
	{
	public:
		virtual ~ITime() = default;
		
		virtual float GetDeltaTime() = 0;
		virtual void SetFramePerSecond(int FramePerSecond) = 0;

	protected:
		long _LastFrameStartTime = 0;
		long _CurrentFrameStartTime = 0;
		float _DeltaTime = 0;
		int _FramesPerSecond = 60;
		long _DesiredFrameDuration = 1000 / 60;

	private:
		//<= 0 for unlimited frame
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void UpdateDeltaTime() = 0;
		virtual void UpdateLastFrameStartTime() = 0;
		virtual void UpdateCurrentFrameStartTime() = 0;
		virtual void ControlFrameRate() = 0;

		virtual void InitialiseTime() override = 0;
		virtual void OnStartFrame() override = 0;
		virtual void OnEndFrame() override = 0;

	};
}