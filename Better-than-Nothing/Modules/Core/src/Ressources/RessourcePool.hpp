#pragma once

#include "Ressources/Texture.hpp"
#include "Ressources/Model.hpp"

namespace BetterThanNothing
{
	class Device;
	class CommandPool;
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
		virtual						~RessourcePool() {}

		virtual T*					GetRessource(const std::string& filePath) = 0;
	};

	typedef std::pair<std::vector<Vertex>, std::vector<u32>>	ModelData;
	typedef std::pair<VkBuffer, VkDeviceMemory>					BufferData;

	class ModelPool: public RessourcePool<Model>
	{
	private:
		Device*			m_Device;
		SwapChain*		m_SwapChain;
	public:
						ModelPool(const std::string& basePath, Device* device, SwapChain* swapChain);
						~ModelPool();

		Model*			GetRessource(const std::string& filePath) override;

	private:

		ModelData		LoadModelData(const std::string& filePath);
		BufferData		CreateVertexBuffer(std::vector<Vertex>& vertices);
		BufferData		CreateIndexBuffer(std::vector<u32>& indices);
	};

	typedef std::pair<VkImage, VkDeviceMemory>	ImageData;

	class TexturePool: public RessourcePool<Texture>
	{
	private:
		Device*			m_Device;
		CommandPool*	m_CommandPool;
		SwapChain*		m_SwapChain;
	public:
						TexturePool(const std::string& basePath, Device* device, CommandPool* commandPool, SwapChain* swapChain);
						~TexturePool();

		Texture*		GetRessource(const std::string& filePath) override;

	private:
		ImageData		CreateTextureImage(const std::string& filePath, u32* mipLevels);
		VkImageView		CreateTextureImageView(VkImage& image, u32 mipLevels);
		VkSampler		CreateTextureSampler(u32 mipLevels);
		void			GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, u32 mipLevels);

	public:
		static void		CreateImage(Device* pDevice, u32 width, u32 height, u32 mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		static void		TransitionImageLayout(SwapChain* pSwapChain, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, u32 mipLevels);
		static void		CopyBufferToImage(SwapChain* pSwapChain, VkBuffer buffer, VkImage image, u32 width, u32 height);
	};
};
