#pragma once

#include "IInterface.h"

namespace NPEngine
{
	class IAudio : public IInterface
	{
	public:
		virtual ~IAudio() = default;

		virtual size_t LoadMusic(const char* Filename) = 0;
		virtual size_t LoadSound(const char* Filename) = 0;

		virtual void PlayMusic(size_t MusicId, int Loop = -1) = 0;
		virtual void PlaySound(size_t SoundId, int Loop = 0) = 0;

		virtual void PauseMusic() = 0;
		virtual void StopMusic() = 0;
		virtual void ResumeMusic() = 0;

		virtual void SetMusicVolume(int Volume) = 0;
		virtual void SetSoundVolume(size_t SoundId, int Volume) = 0;

	private:
		friend class Engine;
		virtual bool Initialize() = 0;
		friend class Engine;
		virtual void Shutdown() = 0;
	};
}