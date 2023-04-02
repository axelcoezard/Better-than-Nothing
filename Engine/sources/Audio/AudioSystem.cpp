#include <iostream>
#include "AudioSystem.hpp"

AudioSystem* AudioSystem::m_Instance = nullptr;

AudioSystem::AudioSystem(void) = default;
AudioSystem::~AudioSystem(void) = default;

bool AudioSystem::Initialize() {
	AudioSystem* instance = AudioSystem::GetInstance();

	instance->m_Device = alcOpenDevice(nullptr);
	if (!instance->m_Device)
		return false;

	instance->m_Context = alcCreateContext(instance->m_Device, nullptr);
	if (!instance->m_Context)
		return false;

	if (!alcMakeContextCurrent(instance->m_Context))
		return false;

	return true;
}

void AudioSystem::GetDevices() {
	AudioSystem* instance = AudioSystem::GetInstance();

	instance->m_Devices.clear();

	const ALCchar* deviceList = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
	while (deviceList != nullptr && std::strlen(deviceList) > 0)
	{
		instance->m_Devices.emplace_back(deviceList);
		deviceList += std::strlen(deviceList) + 1;
	}
}

void AudioSystem::Shutdown() {
	AudioSystem* instance = AudioSystem::GetInstance();

	alcMakeContextCurrent(nullptr);
	if (instance->m_Context != nullptr) {
		alcDestroyContext(instance->m_Context);
	}
	if (instance->m_Device != nullptr) {
		alcCloseDevice(instance->m_Device);
	}
}

uint32_t AudioSystem::LoadSound(const std::string& fileName) {
	SF_INFO fileInfos;
	SNDFILE* file = sf_open(fileName.c_str(), SFM_READ, &fileInfos);
	if (!file)
		return 0;

	auto nbSamples  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
    auto sampleRate = static_cast<ALsizei>(fileInfos.samplerate);

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

AudioSystem* AudioSystem::GetInstance() {
	if (m_Instance == nullptr) {
		m_Instance = new AudioSystem();
	}
	return m_Instance;
}
