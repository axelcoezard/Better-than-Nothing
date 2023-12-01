#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;

	struct RenderPassProperties
	{
		Device* device;
		SwapChain* swapChain;

		VkFormat* swapChainFormat;
		VkExtent2D* swapChainExtent;
		VkSampleCountFlagBits msaaSamples;
	};

	class RenderPass
	{
	protected:
		RenderPassProperties m_Properties;

		std::vector<VkImageView> m_ImageViews;

		std::vector<VkFramebuffer> m_Framebuffers;

		VkImage m_DepthImage;
		VkDeviceMemory m_DepthImageMemory;
		VkImageView m_DepthImageView;

		VkImage m_ColorImage;
		VkDeviceMemory m_ColorImageMemory;
		VkImageView m_ColorImageView;

		VkRenderPass m_RenderPass;

	public:
		RenderPass(RenderPassProperties properties): m_Properties(properties) {}
		virtual ~RenderPass();

		void Create();
		void CreateImageViews();
		void CreateResources();
		void CreateColorResources();
		void CreateDepthResources();
		void CreateRenderPass();
		void CreateFramebuffers();

		void CleanDependencies();
		void RecreateDependencies();

		void GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index);

		VkImageView& GetDepthImageView();
		VkImageView& GetColorImageView();

		VkImageView& GetImageView(u32 index);
		VkFramebuffer& GetFramebuffer(u32 index);

		VkRenderPass& GetVkRenderPass();
	};
};
