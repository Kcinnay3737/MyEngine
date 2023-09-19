#include "Time/SDLTime.h"

#include <time.h>
#include <SDL.h>

using namespace NPEngine;

bool SDLTime::Initialise()
{
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
	long CurrentTime = SDL_GetTicks();

	const int DesiredFrameDuration = 1000 / _FramesPerSecond;
	long CurrentFrameTime = CurrentTime - _CurrentFrameStartTime;

	if (CurrentFrameTime < DesiredFrameDuration)
	{
		SDL_Delay(DesiredFrameDuration - CurrentFrameTime);
	}
}
