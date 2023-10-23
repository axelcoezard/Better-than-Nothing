#pragma once

namespace BetterThanNothing
{
	using SoundID = uint32_t;

	struct Sound
	{
		SoundID			m_Id = 0;
		ALuint			m_Buffer = 0;
		ALuint			m_Source = 0;
		bool			m_IsPlaying = false;
	};

	class AudioSystem
	{
	protected:
		static AudioSystem*			m_pInstance;

		ALCdevice*					m_pDevice = nullptr;
		ALCcontext*					m_pContext = nullptr;

		std::vector<std::string>	m_Devices;
		std::vector<Sound>			m_Sounds;

		AudioSystem();
		~AudioSystem();

	public:
		static bool			Initialize();
		static void			GetDevices();
		static void			Shutdown();

		static SoundID		LoadSound(const std::string& fileName);
		static void			PlaySound(SoundID sound);
		static void			FlushSounds();

	private:
		static AudioSystem*	GetInstance();
	};
}
