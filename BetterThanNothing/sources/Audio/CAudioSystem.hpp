#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

using CAudioBuffer = unsigned int;

class CAudioSystem {
protected:
	static CAudioSystem*		m_pInstance;

	ALCdevice*					m_pDevice = nullptr;
	ALCcontext*					m_pContext = nullptr;

	std::vector<std::string>	m_Devices;

	CAudioSystem();
	~CAudioSystem();

public:
	static bool			Initialize();
	static void			GetDevices();
	static void			Shutdown();

	static uint32_t		LoadSound(const std::string& fileName);
	static void			PlaySound(uint32_t buffer);

private:
	static CAudioSystem*	GetInstance();
};
