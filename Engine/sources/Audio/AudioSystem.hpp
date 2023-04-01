#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

class AudioSystem {
private:
	ALCdevice*					m_Device = nullptr;
	ALCcontext*					m_Context = nullptr;

	std::vector<std::string>	m_Devices;
public:
	AudioSystem(void);
	~AudioSystem(void);

	bool Initialize(void);
	void GetDevices(void);
	void Shutdown(void);

	uint32_t LoadSound(const std::string& fileName);
	void PlaySound(uint32_t buffer);
};
