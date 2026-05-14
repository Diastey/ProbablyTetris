#include "AudioManager.h"
#include <iostream>

AudioManager::~AudioManager()
{
	ReleaseSound();
}

void AudioManager::InitializeAudio()
{
	FMOD_RESULT result;
	// Intialize the FMOD audio
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "SOUND FAILED: System Create | " << FMOD_ErrorString(result) << std::endl;
	}
	result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
	if (result != FMOD_OK)
	{
		std::cout << "SOUND FAILED: Init | " << FMOD_ErrorString(result) << std::endl;
	}
	// Create and initialize the echo audio
	result = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspEcho);
	if (result != FMOD_OK)
	{
		std::cout << "SOUND FAILED: Create DSP By Type | " << FMOD_ErrorString(result) << std::endl;
	}

	// Set parameters for the echo audio
	dspEcho->setParameterFloat(FMOD_DSP_ECHO_DELAY, 215); // Delay time in milliseconds
	dspEcho->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 35); // Feedback level (0 to 100)
	dspEcho->setParameterFloat(FMOD_DSP_ECHO_WETLEVEL, 80); // Wet level (0 to 100)
}

// Play specific audio sound based on index
void AudioManager::PrepareSound1(int soundIndex)
{
	// Check if the sound index is in range of sound array list
	if (soundIndex >= 0 && soundIndex < sounds.size())
	{
		sounds[soundIndex].PrepareSound1(system, baseSoundVolume);
	}
}

// Play specific audio sound based on index and modifier value
void AudioManager::PrepareSound1Ex(int soundIndex, float modifier)
{
	if (soundIndex >= 0 && soundIndex < sounds.size())
	{
		sounds[soundIndex].PrepareSound1(system, baseSoundVolume * modifier);
	}
}

void AudioManager::PlaySound1(int soundIndex, bool play)
{
	if (play)
		sounds.at(soundIndex).Play();
	else
		sounds.at(soundIndex).Pause();
}

// Play the sound track based on index
void AudioManager::PrepareSoundTrack(int soundIndex)
{
	if (soundIndex >= 0 && soundIndex < sounds.size())
	{
		sounds[soundIndex].PrepareSound2(system, baseSoundTrackVolume);
	}
}

// Add all the sound file inside the array vector
void AudioManager::LoadSounds(std::string audioFileName)
{
	//Create new sound and add the sound source to the vector
	Sound newSound = Sound();
	newSound.LoadSound(system, audioFileName);
	sounds.push_back(newSound);
}

// Update the sound files
void AudioManager::UpdateSounds()
{
	FMOD_RESULT result;
	result = system->update();
}

// Release and clear all the audio objects 
void AudioManager::ClearAudio()
{
	for (int i = 0; i < sounds.size(); i++) {
		sounds[i].ReleaseAudio();
	}
	sounds.clear();
}

// Close the FMOD audio
void AudioManager::ReleaseSound()
{
	system->close();
	system->release();
	system = NULL;
}
