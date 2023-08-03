#pragma once

namespace BetterThanNothing
{
	class CWindow;
	class CDevice;
	class CCommandPool;
	class CSwapChain;
	class CDescriptorPool;
	class CTexture;
	class CPipeline;

	class CRenderer
	{
	private:
		CWindow*			m_pWindow;
		CDevice*			m_pDevice;
		CCommandPool*		m_pCommandPool;
		CSwapChain*			m_pSwapChain;
		CDescriptorPool*	m_pDescriptorPool;
		CPipeline*			m_pPipeLine;

	public:
							CRenderer(CWindow* pWindow, CDevice* pDevice);
							~CRenderer();

							CRenderer(const CRenderer&) = delete;
		CRenderer&			operator=(const CRenderer&) = delete;
							CRenderer(CRenderer&&) = delete;
		CRenderer&			operator=(CRenderer&&) = delete;

		void				DrawFrame();

	public:
		CWindow*			GetWindow()			{ return m_pWindow; }
		CDevice*			GetDevice()			{ return m_pDevice; }
		CCommandPool*		GetCommandPool()	{ return m_pCommandPool; }
		CSwapChain*			GetSwapChain()		{ return m_pSwapChain; }
		CDescriptorPool*	GetDescriptorPool()	{ return m_pDescriptorPool; }
		CPipeline*			GetPipeLine()		{ return m_pPipeLine; }
	};
};
