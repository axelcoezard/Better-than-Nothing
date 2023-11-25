#pragma once

#include "GlobalUniforms.hpp"

namespace BetterThanNothing
{
	struct UniformsPerFrameEntry
	{
		GlobalUniforms* m_GlobalUniforms;

		//std::vector<DynamicUniforms*> m_DynamicUniforms;
	};

	class UniformsPool
	{
	private:
		Device* m_Device;

		u32 m_Size;
		u32 m_Capacity;

		std::vector<UniformsPerFrameEntry> m_UniformsPerFrame;
		//std::vector<std::vector<DynamicUniforms*>> m_DynamicUniforms;

	public:
		UniformsPool(Device* device);
		~UniformsPool();

		GlobalUniforms* GetGlobalUniforms(u32 frame);
		//DynamicUniforms* GetData(u32 frame, u32 index);

		u32 GetSize() const;
		u32 GetCapacity() const;
	};
};
