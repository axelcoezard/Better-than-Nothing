#include "Systems/AudioSystem.hpp"

namespace BetterThanNothing
{
	AudioSystem* AudioSystem::m_pInstance = nullptr;

	AudioSystem::AudioSystem() = default;
	AudioSystem::~AudioSystem() = default;

	bool AudioSystem::Initialize()
	{
		AudioSystem* instance = AudioSystem::GetInstance();

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

	void AudioSystem::GetDevices()
	{
		AudioSystem* instance = AudioSystem::GetInstance();

		instance->m_Devices.clear();

		const ALCchar* deviceList = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
		while (deviceList != nullptr && std::strlen(deviceList) > 0)
		{
			instance->m_Devices.emplace_back(deviceList);
			deviceList += std::strlen(deviceList) + 1;
		}
	}

	void AudioSystem::Shutdown()
	{
		AudioSystem* instance = AudioSystem::GetInstance();

		alcMakeContextCurrent(nullptr);

		if (instance->m_pContext != nullptr) {
			alcDestroyContext(instance->m_pContext);
		}

		if (instance->m_pDevice != nullptr) {
			alcCloseDevice(instance->m_pDevice);
		}
	}

	SoundID AudioSystem::LoadSound(const std::string& fileName)
	{
		AudioSystem* instance = AudioSystem::GetInstance();

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

		SoundID id = instance->m_Sounds.size() + 1;
		instance->m_Sounds.push_back({
			.m_Id = id,
			.m_Buffer = buffer,
			.m_IsPlaying = false
		});
		return id;
	}

	void AudioSystem::PlaySound(SoundID id)
	{
		AudioSystem* instance = AudioSystem::GetInstance();

		if (id - 1 >= instance->m_Sounds.size())
			return;

		ALuint source;
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, instance->m_Sounds[id].m_Buffer);
		alSourcePlay(source);

		instance->m_Sounds[id].m_Source = source;
	}


	void AudioSystem::FlushSounds()
	{
		AudioSystem* instance = AudioSystem::GetInstance();

		for (Sound& sound : instance->m_Sounds)
		{
			ALint state;
			alGetSourcei(sound.m_Source, AL_SOURCE_STATE, &state);
			if (state != AL_STOPPED) {
				continue;
			}

			alDeleteBuffers(1, &sound.m_Buffer);
			alSourcei(sound.m_Source, AL_BUFFER, 0);
			alDeleteSources(1, &sound.m_Source);

			for (auto it = instance->m_Sounds.begin(); it != instance->m_Sounds.end(); it++) {
				if (it->m_Id == sound.m_Id) {
					instance->m_Sounds.erase(it);
					break;
				}
			}
		}
	}

	AudioSystem* AudioSystem::GetInstance()
	{
		if (m_pInstance == nullptr) {
			m_pInstance = new AudioSystem();
		}
		return m_pInstance;
	}
};
