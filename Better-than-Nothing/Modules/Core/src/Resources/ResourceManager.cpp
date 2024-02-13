#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	ResourceManager::ResourceManager(Device* device, const std::string& assetsPath)
		: m_Device(device)
	{
		m_ShaderPool = new ShaderPool(assetsPath, device);
		m_ModelPool = new ModelPool(assetsPath, device);
		m_TexturePool = new TexturePool(assetsPath, device);
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

	ShaderPool* ResourceManager::GetShaderPool() const
	{
		return m_ShaderPool;
	}

	ModelPool* ResourceManager::GetModelPool() const
	{
		return m_ModelPool;
	}

	TexturePool* ResourceManager::GetTexturePool() const
	{
		return m_TexturePool;
	}
};
