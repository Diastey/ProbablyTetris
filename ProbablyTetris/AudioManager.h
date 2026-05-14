#pragma once
#include "Sound.h"
#include <vector>

class AudioManager
{
	static AudioManager* instance;

	//Virtual Soundcard
	FMOD::System* system = nullptr;
	void* extraDriverData = 0;
	std::vector<Sound> sounds;
	FMOD::DSP* dspEcho = nullptr;
	float baseSoundVolume = 1;
	float baseSoundTrackVolume = 1;

public:
	AudioManager() = default;
	~AudioManager();
	static AudioManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new AudioManager();
		}
		return instance;
	}

	void InitializeAudio();
	//Prepare to play sound1
	void PrepareSound1(int soundIndex);
	void PrepareSound1Ex(int soundIndex, float modifier);
	void PlaySound1(int soundIndex, bool play);
	void PrepareSoundTrack(int soundIndex);
	void LoadSounds(std::string audioFileName);
	//Update the channel (Almomst like game update but is for sound)
	void UpdateSounds();

	void ClearAudio();
	void ReleaseSound();
	static void DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
};

