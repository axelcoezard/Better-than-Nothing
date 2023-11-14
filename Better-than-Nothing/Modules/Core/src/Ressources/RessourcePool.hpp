#pragma once

#include "Ressources/Texture.hpp"
#include "Ressources/Model.hpp"

namespace BetterThanNothing
{
	class Device;
	class SwapChain;
	class Vertex;

	template <typename T>
	class RessourcePool
	{
	protected:
		std::string					m_BasePath;
		std::map<std::string, T*>	m_Ressources;
	public:
									RessourcePool(const std::string& basePath): m_BasePath(basePath) {}
									~RessourcePool() {}

		virtual T*					GetRessource(const std::string& filePath) = 0;
	};

	class TexturePool: public RessourcePool<Texture>
	{
	private:
		Device*						m_pDevice;
		SwapChain*					m_pSwapChain;
	public:
									TexturePool(const std::string& basePath, Device* device, SwapChain* swapChain);
									~TexturePool();

		Texture*					GetRessource(const std::string& filePath) override;
	};

	typedef std::pair<std::vector<Vertex>, std::vector<u32>>	ModelData;
	typedef std::pair<VkBuffer, VkDeviceMemory>					BufferData;

	class ModelPool: public RessourcePool<Model>
	{
	private:
		Device*						m_Device;
		SwapChain*					m_SwapChain;
	public:
									ModelPool(const std::string& basePath, Device* device, SwapChain* swapChain);
									~ModelPool();

		Model*						GetRessource(const std::string& filePath) override;

	private:

		ModelData					LoadModelData(const std::string& filePath);
		BufferData					CreateVertexBuffer(std::vector<Vertex>& vertices);
		BufferData					CreateIndexBuffer(std::vector<u32>& indices);
	};
};
