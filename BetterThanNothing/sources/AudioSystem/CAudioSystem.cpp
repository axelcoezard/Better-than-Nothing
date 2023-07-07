#include <iostream>
#include "AudioSystem/CAudioSystem.hpp"

namespace BetterThanNothing {
	CAudioSystem* CAudioSystem::m_pInstance = nullptr;

	CAudioSystem::CAudioSystem(void) = default;
	CAudioSystem::~CAudioSystem(void) = default;

	bool CAudioSystem::Initialize() {
		CAudioSystem* instance = CAudioSystem::GetInstance();

		instance->m_pDevice = alcOpenDevice(nullptr);
		if (!instance->m_pDevice)
			return false;

		instance->m_pContext = alcCreateContext(instance->m_pDevice, nullptr);
		if (!instance->m_pContext)
			return false;

		if (!alcMakeContextCurrent(instance->m_pContext))
			return false;

		return true;
	}

	void CAudioSystem::GetDevices() {
		CAudioSystem* instance = CAudioSystem::GetInstance();

		instance->m_Devices.clear();

		const ALCchar* deviceList = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
		while (deviceList != nullptr && std::strlen(deviceList) > 0)
		{
			instance->m_Devices.emplace_back(deviceList);
			deviceList += std::strlen(deviceList) + 1;
		}
	}

	void CAudioSystem::Shutdown() {
		CAudioSystem* instance = CAudioSystem::GetInstance();

		alcMakeContextCurrent(nullptr);
		if (instance->m_pContext != nullptr) {
			alcDestroyContext(instance->m_pContext);
		}
		if (instance->m_pDevice != nullptr) {
			alcCloseDevice(instance->m_pDevice);
		}
	}

	uint32_t CAudioSystem::LoadSound(const std::string& fileName) {
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

	void CAudioSystem::PlaySound(uint32_t buffer) {
		ALuint source;
		alGenSources(1, &source);

		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);

		// TODO: Delete sound when fully played
		//alDeleteBuffers(1, &buffer);
		//alSourcei(source, AL_BUFFER, 0);
		//alDeleteSources(1, &source);
	}

	CAudioSystem* CAudioSystem::GetInstance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CAudioSystem();
		}
		return m_pInstance;
	}
};
