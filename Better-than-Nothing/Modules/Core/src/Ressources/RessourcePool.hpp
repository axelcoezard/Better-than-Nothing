#pragma once

#include "Ressources/Texture.hpp"
#include "Ressources/Model.hpp"

namespace BetterThanNothing
{
	class Device;
	class CommandPool;
	class SwapChain;
	class Vertex;
	class Buffer;

	template <typename T>
	class RessourcePool
	{
	protected:
		std::string							m_BasePath;
		std::unordered_map<std::string, T*>	m_Ressources;
	public:
									RessourcePool(const std::string& basePath): m_BasePath(basePath) {}
		virtual						~RessourcePool() {}

		virtual T*					GetRessource(const std::string& filePath) = 0;
	};

	typedef std::pair<std::vector<Vertex>, std::vector<u32>>	ModelData;

	class ModelPool: public RessourcePool<Model>
	{
	private:
		Device*			m_Device;

	public:
						ModelPool(const std::string& basePath, Device* device);
						~ModelPool();

		Model*			GetRessource(const std::string& filePath) override;

	private:

		ModelData		LoadModelData(const std::string& filePath);
		Buffer			CreateVertexBuffer(std::vector<Vertex>& vertices);
		Buffer			CreateIndexBuffer(std::vector<u32>& indices);
	};

	typedef std::pair<VkImage, VkDeviceMemory>	ImageData;

	class TexturePool: public RessourcePool<Texture>
	{
	private:
		Device*			m_Device;

	public:
						TexturePool(const std::string& basePath, Device* device);
						~TexturePool();

		Texture*		GetRessource(const std::string& filePath) override;

	private:
		ImageData		CreateTextureImage(const std::string& filePath, u32* mipLevels);
		VkImageView		CreateTextureImageView(VkImage& image, u32 mipLevels);
		VkSampler		CreateTextureSampler(u32 mipLevels);
		void			GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, u32 mipLevels);
	};
};
