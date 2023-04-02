#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

using AudioBuffer = unsigned int;

class AudioSystem {
protected:
	static AudioSystem*			m_Instance;

	ALCdevice*					m_Device = nullptr;
	ALCcontext*					m_Context = nullptr;

	std::vector<std::string>	m_Devices;

	AudioSystem();
	~AudioSystem();

public:
	static bool			Initialize();
	static void			GetDevices();
	static void			Shutdown();

	static uint32_t		LoadSound(const std::string& fileName);
	static void			PlaySound(uint32_t buffer);

private:
	static AudioSystem*	GetInstance();
};
