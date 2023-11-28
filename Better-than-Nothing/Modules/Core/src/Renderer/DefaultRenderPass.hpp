#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	class DefaultRenderPass: public RenderPass
	{
	public:
		DefaultRenderPass(RenderPassProperties properties): RenderPass(properties) {}
		~DefaultRenderPass() = default;

		void CreateRenderPass() override;
		void GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index) override;
	};
};
