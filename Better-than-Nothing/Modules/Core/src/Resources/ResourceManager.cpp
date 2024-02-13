#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	ResourceManager::ResourceManager(Device* device, const std::string& assetsPath)
		: m_Device(device)
	{
		m_ShaderPool = new ShaderPool(assetsPath + "/Shaders/", device);
		m_ModelPool = new ModelPool(assetsPath + "/Models/", device);
		m_TexturePool = new TexturePool(assetsPath + "/Models/", device);
	}

	ResourceManager::~ResourceManager()
	{
		delete m_ShaderPool;
		delete m_ModelPool;
		delete m_TexturePool;
	}

	Shader* ResourceManager::GetShader(const std::string& path)
	{
		return m_ShaderPool->GetResource(path);
	}

	Model* ResourceManager::GetModel(const std::string& path)
	{
		return m_ModelPool->GetResource(path);
	}

	Texture* ResourceManager::GetTexture(const std::string& path)
	{
		return m_TexturePool->GetResource(path);
	}
};
