#include "Audio/SDLAudio.h"

#include "Engine.h"
#include "Debug/Logger/ILogger.h"
#include <SDL_mixer.h>

using namespace NPEngine;

bool SDLAudio::Initialize()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		Engine::GetLogger()->LogMessage(SDL_GetError());
		return false;
	}

	return true;
}

void SDLAudio::Shutdown()
{
	Mix_CloseAudio();
}

size_t SDLAudio::LoadMusic(const char* Filename)
{
	std::hash<const char*> Hasher;
	size_t MusicId = Hasher(Filename);

	if (_MusicMap.find(MusicId) == _MusicMap.end())
	{
		std::string FilePath = "../Assets/Audio/Music/";
		FilePath += Filename;
		Mix_Music* Music = Mix_LoadMUS(FilePath.c_str());
		if (Music)
		{
			_MusicMap[MusicId] = Music;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Music not found");
		}
	}

	return MusicId;
}

size_t SDLAudio::LoadSound(const char* Filename)
{
	std::hash<const char*> Hasher;
	size_t SoundId = Hasher(Filename);

	if (_SoundMap.find(SoundId) == _SoundMap.end())
	{
		std::string FilePath = "../Assets/Audio/Sound/";
		FilePath += Filename;
		Mix_Chunk* Sound = Mix_LoadWAV(FilePath.c_str());
		if (Sound)
		{
			_SoundMap[SoundId] = Sound;
		}
		else
		{
			Engine::GetLogger()->LogMessage("Sound effect not found");
		}
	}

	return SoundId;
}

void SDLAudio::PlayMusic(size_t MusicId, int Loop)
{
	Mix_Music* Music = _MusicMap[MusicId];
	if (Music)
	{
		if (Mix_PlayMusic(Music, Loop) == -1)
		{
			Engine::GetLogger()->LogMessage("Failed to play music");
		}
	}
	else
	{
		Engine::GetLogger()->LogMessage("Music not found");
	}
}

void SDLAudio::PlaySound(size_t SoundId, int Loop)
{
	Mix_Chunk* Sound = _SoundMap[SoundId];
	if (Sound)
	{
		if (Mix_PlayChannel(-1, Sound, Loop) == -1)
		{
			Engine::GetLogger()->LogMessage("Failed to play sound");
		}
	}
	else
	{
		Engine::GetLogger()->LogMessage("Sound not found");
	}
}

void SDLAudio::PauseMusic()
{
	Mix_PauseMusic();
}

void SDLAudio::StopMusic()
{
	Mix_HaltMusic();
}

void SDLAudio::ResumeMusic()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void SDLAudio::SetMusicVolume(int Volume)
{
	Volume = std::max(0, std::min(Volume, MIX_MAX_VOLUME));
	Mix_VolumeMusic(Volume);
}

void SDLAudio::SetSoundVolume(size_t SoundId, int Volume)
{
	Mix_Chunk* Sound = _SoundMap[SoundId];
	if (Sound)
	{
		Volume = std::max(0, std::min(Volume, MIX_MAX_VOLUME));
		Mix_VolumeChunk(Sound, Volume);
	}
	else
	{
		Engine::GetLogger()->LogMessage("Sound not found");
	}
}