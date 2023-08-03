#include "CRenderer.hpp"

#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CDescriptorPool.hpp"
#include "Engine/CTexture.hpp"
#include "Engine/CPipeline.hpp"

namespace BetterThanNothing
{
	CRenderer::CRenderer(CWindow* pWindow, CDevice* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pCommandPool = new CCommandPool(m_pDevice);
		m_pSwapChain = new CSwapChain(m_pWindow, m_pDevice, m_pCommandPool);
		m_pDescriptorPool = new CDescriptorPool(m_pDevice, m_pSwapChain);

		// one per shaders couple
		m_pPipeLine = new CPipeline(m_pDevice, m_pSwapChain, m_pDescriptorPool);
	}

	CRenderer::~CRenderer()
	{
		delete m_pPipeLine;
		delete m_pDescriptorPool;
		delete m_pSwapChain;
		delete m_pCommandPool;
	}

	void CRenderer::DrawFrame() {
		m_pSwapChain->DrawFrame(m_pDescriptorPool, m_pPipeLine);
	}
}
