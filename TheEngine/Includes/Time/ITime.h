#pragma once

namespace NPEngine
{
	class ITime
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
		friend class Engine;
		virtual void UpdateDeltaTime() = 0;
		friend class Engine;
		virtual void UpdateLastFrameStartTime() = 0;
		friend class Engine;
		virtual void UpdateCurrentFrameStartTime() = 0;
		friend class Engine;
		virtual void ControlFrameRate() = 0;

	};
}