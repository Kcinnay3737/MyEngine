#include "Time/SDLTime.h"

#include <time.h>
#include <SDL.h>

using namespace NPEngine;

bool SDLTime::Initialise(int FramePerSecond)
{
	SetFramePerSecond(FramePerSecond);
	return true;
}

void SDLTime::Shutdown()
{
}

float SDLTime::GetDeltaTime()
{
	return _DeltaTime;
}

void SDLTime::SetFramePerSecond(int FramePerSecond)
{
	_FramesPerSecond = FramePerSecond;
	if (_FramesPerSecond <= 0) return;
	_DesiredFrameDuration = 1000 / FramePerSecond;
}

void SDLTime::UpdateDeltaTime()
{
	_DeltaTime = (_CurrentFrameStartTime - _LastFrameStartTime) * 0.001f;
}

void SDLTime::UpdateLastFrameStartTime()
{
	_LastFrameStartTime = _CurrentFrameStartTime;
}

void SDLTime::UpdateCurrentFrameStartTime()
{
	_CurrentFrameStartTime = SDL_GetTicks();
}

void SDLTime::ControlFrameRate()
{
	if (_FramesPerSecond <= 0) return;

	long CurrentTime = SDL_GetTicks();

	long CurrentFrameTime = CurrentTime - _CurrentFrameStartTime;

	if (CurrentFrameTime < _DesiredFrameDuration)
	{
		SDL_Delay(_DesiredFrameDuration - CurrentFrameTime);
	}
}

void SDLTime::InitialiseTime()
{
	UpdateCurrentFrameStartTime();
	UpdateLastFrameStartTime();
}

void SDLTime::OnStartFrame()
{
	UpdateCurrentFrameStartTime();
	UpdateDeltaTime();
}

void SDLTime::OnEndFrame()
{
	ControlFrameRate();
	UpdateLastFrameStartTime();
}