/*
 * File: AudioSystem.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 5:46:37 pm
 * Last Modified: Saturday, 25th March 2023 6:02:33 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>
#include "AudioSystem.hpp"

AudioSystem::AudioSystem(void) {};
AudioSystem::~AudioSystem(void) {};

bool AudioSystem::Initialize(void) {
	m_Device = alcOpenDevice(NULL);
	if (!m_Device)
		return false;

	m_Context = alcCreateContext(m_Device, NULL);
	if (!m_Context)
		return false;

	if (!alcMakeContextCurrent(m_Context))
		return false;

	return true;
}

void AudioSystem::GetDevices(void) {
	m_Devices.clear();

	const ALCchar* deviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	while (deviceList != nullptr && std::strlen(deviceList) > 0)
	{
		std::cout << deviceList << std::endl;
		m_Devices.push_back(deviceList);
		deviceList += std::strlen(deviceList) + 1;
	}
}

void AudioSystem::Shutdown(void) {
	alcMakeContextCurrent(NULL);
	if (m_Context != nullptr) {
		alcDestroyContext(m_Context);
	}
	if (m_Device != nullptr) {
		alcCloseDevice(m_Device);
	}
}

uint32_t AudioSystem::LoadSound(const std::string& fileName) {
	SF_INFO fileInfos;
	SNDFILE* file = sf_open(fileName.c_str(), SFM_READ, &fileInfos);
	if (!file)
		return 0;

	ALsizei nbSamples  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
	ALsizei sampleRate = static_cast<ALsizei>(fileInfos.samplerate);

	std::vector<ALshort> Samples(nbSamples);
	if (sf_read_short(file, &Samples[0], nbSamples) < nbSamples)
		return 0;
	sf_close(file);

	ALenum fileFormat;
	switch (fileInfos.channels)
	{
		case 1 :  fileFormat = AL_FORMAT_MONO16;   break;
		case 2 :  fileFormat = AL_FORMAT_STEREO16; break;
		default : return 0;
	}

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, fileFormat, &Samples[0], nbSamples * sizeof(ALushort), sampleRate);
	if (alGetError() != AL_NO_ERROR)
		return 0;

	return buffer;
}

void AudioSystem::PlaySound(uint32_t buffer) {
	ALuint source;
	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);

	// TODO: Delete sound when fully played
	//alDeleteBuffers(1, &buffer);
	//alSourcei(source, AL_BUFFER, 0);
	//alDeleteSources(1, &source);
}

