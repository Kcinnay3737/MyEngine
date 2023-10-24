#pragma once

#include "IInterface.h"

namespace NPEngine
{
	class ITime : public IInterface
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
		friend class Engine;
		virtual bool Initialise(int FramePerSecond = 60) = 0;
		friend class Engine;
		virtual void Shutdown() = 0;

		virtual void UpdateDeltaTime() = 0;
		virtual void UpdateLastFrameStartTime() = 0;
		virtual void UpdateCurrentFrameStartTime() = 0;
		virtual void ControlFrameRate() = 0;

		friend class Engine;
		virtual void InitialiseTime() = 0;
		friend class Engine;
		virtual void OnStartFrame() = 0;
		friend class Engine;
		virtual void OnEndFrame() = 0;

	};
}