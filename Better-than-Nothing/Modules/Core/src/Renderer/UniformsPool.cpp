#include "UniformsPool.hpp"

namespace BetterThanNothing
{
	UniformsPool::UniformsPool(Device* device): m_Device(device)
	{
		m_Size = 0;
		m_Capacity = 1000;

		m_UniformsPerFrame.resize(MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformsPerFrame[i].m_GlobalUniforms = nullptr;
		}
	}

	UniformsPool::~UniformsPool()
	{
		m_UniformsPerFrame.clear();
	}

	GlobalUniforms* UniformsPool::GetGlobalUniforms(u32 frame)
	{
		UniformsPerFrameEntry& ref = m_UniformsPerFrame[frame];
		if (ref.m_GlobalUniforms == nullptr) {
			ref.m_GlobalUniforms = new GlobalUniforms();
		}
		return ref.m_GlobalUniforms;
	}

	//DynamicUniforms* UniformsPool::GetData(u32 frame, u32 index)
	//{
	//	return m_DynamicUniforms[frame][index];
	//}

	u32 UniformsPool::GetSize() const
	{
		return m_Size;
	}

	u32 UniformsPool::GetCapacity() const
	{
		return m_Capacity;
	}
};
