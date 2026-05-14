#pragma once
#include "fmod.hpp"
#include <fmod_errors.h>
#include <string>
#include <iostream>

class Sound
{
	//Sound files
	FMOD::Sound* sound1;
	FMOD::Sound* sound2;
	FMOD::Channel* channel;

public:
	Sound() = default;
	~Sound() = default;

	//Read harddisk, read the sound, load into the sound card memory
	void LoadSound(FMOD::System* system, std::string audioFileName)
	{
		FMOD_RESULT result;
		// Create the sound files based on the sound file names
		result = system->createSound(audioFileName.c_str(), FMOD_DEFAULT, 0, &sound1);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Create sound1 (" << audioFileName << ") | " << FMOD_ErrorString(result) << std::endl;
		}
		result = sound1->setMode(FMOD_LOOP_OFF);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Set sound1 mode (" << audioFileName << ") | " << FMOD_ErrorString(result) << std::endl;
		}
		result = system->createStream(audioFileName.c_str(), FMOD_DEFAULT, 0, &sound2);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Create sound2 (" << audioFileName << ") | " << FMOD_ErrorString(result) << std::endl;
		}
		result = sound2->setMode(FMOD_LOOP_OFF);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Set sound2 mode (" << audioFileName << ") | " << FMOD_ErrorString(result) << std::endl;
		}
	}
	//Prepare to play sound1 (Need to setPause to false afterwards to play)
	void PrepareSound1(FMOD::System* system, float baseSoundVolume)
	{
		FMOD_RESULT result;
		result = system->playSound(sound1, 0, true, &channel);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Prepare sound1 | " << FMOD_ErrorString(result) << std::endl;
		}
		channel->setVolume(baseSoundVolume);
	}
	//Prepare to play sound2 (Need to setPause to false afterwards to play)
	void PrepareSound2(FMOD::System* system, float baseSoundTrackVolume)
	{
		FMOD_RESULT result;
		result = system->playSound(sound2, 0, true, &channel);
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Prepare sound2 | " << FMOD_ErrorString(result) << std::endl;
		}
		channel->setVolume(baseSoundTrackVolume);
	}
	void ReleaseAudio()
	{
		FMOD_RESULT result;
		result = sound1->release();
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Release sound1 | " << result << std::endl;
		}
		sound1 = NULL;
		result = sound2->release();
		if (result != FMOD_OK)
		{
			std::cout << "SOUND FAILED: Release sound2 | " << result << std::endl;
		}
		sound2 = NULL;

	}
	void Play()
	{
		channel->setPaused(false);
	}
	void Pause()
	{
		channel->setPaused(true);
	}
};

