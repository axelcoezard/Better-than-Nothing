#pragma once

#include <map>
namespace BetterThanNothing
{
	class CWindow;
	class CDevice;
	class CCommandPool;
	class CSwapChain;
	class CDescriptorPool;
	class CTexture;
	class CPipeline;
	class CModel;

	class CRenderer
	{
	private:
		CWindow*							m_pWindow;
		CDevice*							m_pDevice;
		CCommandPool*						m_pCommandPool;
		CSwapChain*							m_pSwapChain;
		CDescriptorPool*					m_pDescriptorPool;

		std::map<std::string, CPipeline*>	m_pPipeLines;
		std::vector<CModel*>				m_pModels;

	public:
											CRenderer(CWindow* pWindow, CDevice* pDevice);
											~CRenderer();

											CRenderer(const CRenderer&) = delete;
		CRenderer&							operator=(const CRenderer&) = delete;
											CRenderer(CRenderer&&) = delete;
		CRenderer&							operator=(CRenderer&&) = delete;

	public:
		void								LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void								LoadModel(const std::string& modelPath, const std::string& texturePath);

		void								PrepareFrame();
		void								Render();

		void								MoveCamera(float x, float y, float z);

	public:
		CWindow*							GetWindow()			{ return m_pWindow; }
		CDevice*							GetDevice()			{ return m_pDevice; }
		CCommandPool*						GetCommandPool()	{ return m_pCommandPool; }
		CSwapChain*							GetSwapChain()		{ return m_pSwapChain; }
		CDescriptorPool*					GetDescriptorPool()	{ return m_pDescriptorPool; }
		std::map<std::string, CPipeline*>	GetPipeLines()		{ return m_pPipeLines; }
		std::vector<CModel*>				GetModels()			{ return m_pModels; }
	};
};
