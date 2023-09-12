#include "Time/SDLTime.h"

#include <time.h>
#include <SDL.h>

float NPEngine::SDLTime::GetDeltaTime()
{
	return _DeltaTime;
}

void NPEngine::SDLTime::SetFramePerSecond(int FramePerSecond)
{
	_FramesPerSecond = FramePerSecond;
	_DesiredFrameDuration = 1000 / FramePerSecond;
}

void NPEngine::SDLTime::UpdateDeltaTime()
{
	_DeltaTime = (_CurrentFrameStartTime - _LastFrameStartTime) * 0.001f;
}

void NPEngine::SDLTime::UpdateLastFrameStartTime()
{
	_LastFrameStartTime = _CurrentFrameStartTime;
}

void NPEngine::SDLTime::UpdateCurrentFrameStartTime()
{
	_CurrentFrameStartTime = SDL_GetTicks();
}

void NPEngine::SDLTime::ControlFrameRate()
{
	long CurrentTime = SDL_GetTicks();

	const int DesiredFrameDuration = 1000 / _FramesPerSecond;
	long CurrentFrameTime = CurrentTime - _CurrentFrameStartTime;

	if (CurrentFrameTime < DesiredFrameDuration)
	{
		SDL_Delay(DesiredFrameDuration - CurrentFrameTime);
	}
}
