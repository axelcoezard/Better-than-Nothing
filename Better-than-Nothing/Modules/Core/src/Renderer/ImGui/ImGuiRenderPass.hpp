#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	class ImGuiRenderPass: public RenderPass
	{
	public:
		ImGuiRenderPass(RenderPassProperties properties): RenderPass(properties) {}
		~ImGuiRenderPass() = default;

		void CreateRenderPass() override;
		void GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index) override;
	};
};
