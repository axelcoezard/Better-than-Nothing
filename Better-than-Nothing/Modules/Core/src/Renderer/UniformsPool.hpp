#pragma once

#include "GlobalUniforms.hpp"
#include "DynamicUniforms.hpp"

namespace BetterThanNothing
{
	class Device;
	class SwapChain;

	/**
	 * @brief The uniforms is pool used to store the global and dynamic uniforms
	 * @note The global uniforms are the same for all entities, 1 per frame (camera, lights, etc.)
	 * @note The dynamic uniforms are different for each entity, 1 per entity per frame (model matrix, material, etc.)
	 */
	class UniformsPool
	{
	private:
		/**
		 * @brief The pointer to the device
		 */
		Device* m_Device;

		/**
		 * @brief The current size of the pool
		 */
		u32 m_Size;

		/**
		 * @brief The total capacity of the pool
		 */
		u32 m_Capacity;

		/**
		 * @brief The global uniforms
		 * @note 1 per frame
		 */
		std::vector<Buffer*> m_GlobalUniforms; // 1 per frame

		/**
		 * @brief The dynamic uniforms
		 * @note 1 per entity per frame
		 */
		std::vector<std::vector<Buffer*>> m_DynamicUniforms; // 1 per entity per frame

	public:
		/**
		 * @brief Construct a new UniformsPool object
		 *
		 * @param device The pointer to the device
		 */
		UniformsPool(Device* device);

		/**
		 * @brief Destroy the UniformsPool object
		 */
		~UniformsPool();

	private:
		/**
		 * @brief Create the pools
		 */
		void CreateUniformsPool(u32 newCapacity);

		/**
		 * @brief Destroy the pools
		 */
		void DestroyUniformsPool();

		/**
		 * @brief Allocate all the global uniforms
		 */
		void AllocateAllGlobalUniforms();

	public:
		/**
		 * @brief Extend the pool
		 */
		void ExtendUniformsPool();

		/**
		 * @brief Create a new dynamic uniform
		 *
		 * @return The pointer to the new dynamic uniforms (1 per frame)
		 */
		std::vector<Buffer*>& CreateDynamicUniforms();

		/**
		 * @brief Get all the global uniforms
		 *
		 * @return The pointer to the global uniforms (1 per frame)
		 */
		std::vector<Buffer*>& GetAllGlobalUniforms();

		/**
		 * @brief Get the global uniforms for a frame
		 *
		 * @param frame The frame
		 * @return The pointer to the global uniforms (1 per frame)
		 */
		GlobalUniforms* GetGlobalUniforms(u32 frame);

		/**
		 * @brief Get the dynamic uniforms for a frame and an index
		 *
		 * @param frame The frame
		 * @param index The index
		 * @return The pointer to the dynamic uniforms (1 per entity per frame)
		 */
		DynamicUniforms* GetDynamicUniforms(u32 frame, u32 index);

		/**
		 * @brief Check if the pool should be extended
		 *
		 * @return true if the pool should be extended
		 * @return false if the pool should not be extended
		 */
		bool ShouldExtends() const;

		/**
		 * @brief Get the size of the pool
		 *
		 * @return The size of the pool
		 */
		u32 GetSize() const;

		/**
		 * @brief Get the capacity of the pool
		 *
		 * @return The capacity of the pool
		 */
		u32 GetCapacity() const;
	};
};
