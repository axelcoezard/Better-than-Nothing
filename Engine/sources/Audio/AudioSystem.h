/*
 * File: AudioSystem.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 6:03:04 pm
 * Last Modified: Saturday, 25th March 2023 6:03:06 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

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
	ALCdevice* m_Device = nullptr;
	ALCcontext* m_Context = nullptr;

	std::vector<std::string> m_Devices;
public:
	AudioSystem(void);
	~AudioSystem(void);

	bool Initialize(void);
	void GetDevices(void);
	void Shutdown(void);

	uint32_t LoadSound(const std::string& fileName);
	void PlaySound(uint32_t buffer);
};
