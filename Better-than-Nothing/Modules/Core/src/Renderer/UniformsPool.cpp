#include "UniformsPool.hpp"

namespace BetterThanNothing
{
	UniformsPool::UniformsPool(Device* device): m_Device(device)
	{
		CreateUniformsPool(1000);
		AllocateAllGlobalUniforms();
	}

	UniformsPool::~UniformsPool()
	{
		DestroyUniformsPool();
	}

	void UniformsPool::CreateUniformsPool(u32 newCapacity)
	{
		// Reset the size and capacity
		m_Size = 0;
		m_Capacity = newCapacity;

		// Create the global uniforms (1 per frame)
		m_GlobalUniforms.resize(MAX_FRAMES_IN_FLIGHT);

		// Create the dynamic uniforms (capacity per frame)
		m_DynamicUniforms.resize(m_Capacity);
		for (u32 i = 0; i < m_Capacity; i++) {
			m_DynamicUniforms[i].resize(MAX_FRAMES_IN_FLIGHT);
		}
	}

	void UniformsPool::ExtendUniformsPool()
	{
		u32 oldCapacity = m_Capacity;
		u32 newCapacity = m_Capacity * 2;

		m_DynamicUniforms.resize(newCapacity);
		for (u32 i = oldCapacity; i < newCapacity; i++) {
			m_DynamicUniforms[i].resize(MAX_FRAMES_IN_FLIGHT);
		}

		m_Capacity = newCapacity;
	}

	void UniformsPool::DestroyUniformsPool()
	{
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_Device->DestroyBuffer(m_GlobalUniforms[i]);
		}
		m_GlobalUniforms.clear();

		for (u32 i = 0; i < m_Capacity; i++) {
			for (u32 j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
				m_Device->DestroyBuffer(m_DynamicUniforms[i][j]);
			}
		}
		m_DynamicUniforms.clear();
	}

	void UniformsPool::AllocateAllGlobalUniforms()
	{
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_GlobalUniforms[i] = new Buffer();

			m_Device->CreateBuffer(
				m_GlobalUniforms[i],
				sizeof(GlobalUniforms),
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(m_GlobalUniforms[i], 0, 0, &m_GlobalUniforms[i]->m_Mapped);
		}
	}

	std::vector<Buffer*>& UniformsPool::CreateDynamicUniforms()
	{
		u32 oldSize = m_Size;
		u32 newSize = m_Size + 1;

		for (u32 frameIndex = 0; frameIndex < MAX_FRAMES_IN_FLIGHT; frameIndex++)
		{
			m_DynamicUniforms[m_Size][frameIndex] = new Buffer();

			m_Device->CreateBuffer(
				m_DynamicUniforms[m_Size][frameIndex],
				sizeof(GlobalUniforms),
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(m_DynamicUniforms[m_Size][frameIndex], 0, 0, &m_DynamicUniforms[m_Size][frameIndex]->m_Mapped);
		}

		m_Size  = newSize;
		return m_DynamicUniforms[oldSize];
	}


	std::vector<Buffer*>& UniformsPool::GetAllGlobalUniforms()
	{
		return m_GlobalUniforms;
	}

	GlobalUniforms* UniformsPool::GetGlobalUniforms(u32 frame)
	{
		if (frame >= MAX_FRAMES_IN_FLIGHT) {
			throw std::runtime_error("UniformsPool::GetGlobalUniforms: frame >= MAX_FRAMES_IN_FLIGHT");
		}
		return static_cast<GlobalUniforms*>(m_GlobalUniforms[frame]->m_Mapped);
	}

	DynamicUniforms* UniformsPool::GetDynamicUniforms(u32 frame, u32 index)
	{
		if (index >= m_Capacity) {
			throw std::runtime_error("UniformsPool::GetDynamicUniforms: index >= m_Capacity");
		}
		return static_cast<DynamicUniforms*>(m_DynamicUniforms[index][frame]->m_Mapped);
	}


	bool UniformsPool::ShouldExtends() const
	{
		return m_Size >= m_Capacity;
	}

	u32 UniformsPool::GetSize() const
	{
		return m_Size;
	}

	u32 UniformsPool::GetCapacity() const
	{
		return m_Capacity;
	}
};
