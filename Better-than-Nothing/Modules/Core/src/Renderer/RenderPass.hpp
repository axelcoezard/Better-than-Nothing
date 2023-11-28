#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;

	#define RENDER_PASS_ATTACHMENT_TYPE_COLOR 0x01
	#define RENDER_PASS_ATTACHMENT_TYPE_DEPTH 0x02

	struct RenderPassProperties
	{
		Device* device;
		SwapChain* swapChain;

		VkFormat swapChainFormat;
		VkExtent2D swapChainExtent;
		VkSampleCountFlagBits msaaSamples;

		u32 attachmentTypeFlags;
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
		virtual void CreateRenderPass() = 0;
		void CreateFramebuffers();

		void CleanDependencies();
		void RecreateDependencies();

		virtual void GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index) = 0;

		VkImageView& GetDepthImageView();
		VkImageView& GetColorImageView();

		VkImageView& GetImageView(u32 index);
		VkFramebuffer& GetFramebuffer(u32 index);

		VkRenderPass& GetVkRenderPass();
	};
};
