#pragma once

#include <vector>
#include <map>
#include <bitset>

#include "Entity.hpp"
#include "Component.hpp"

#define MAX_COMPONENTS 32

namespace BetterThanNothing
{
	class ECSManager
	{
	private:
		uint32_t													m_NextEntityId = 0;
		std::vector<uint32_t>										m_FreedEntityIds;
		std::vector<std::bitset<MAX_COMPONENTS>>					m_EntityToBitset;

		std::map<std::string, uint32_t>								m_ComponentsId;

						ECSManager(const ECSManager&) = delete;
		ECSManager&		operator=(const ECSManager&) = delete;
						ECSManager(ECSManager&&) = delete;
		ECSManager&		operator=(ECSManager&&) = delete;

	public:
		ECSManager()
		{

		}

		~ECSManager()
		{
			RemoveAllEntities();
		}

		template<typename T>
		bool RegisterComponent()
		{
			static uint32_t nextComponentId = 0;

			if (nextComponentId >= MAX_COMPONENTS) {
				return false;
			}

			if(!std::is_base_of<Component, T>::value) {
				return false;
			}
			if (m_ComponentsId.find(T::GetStaticName()) != m_ComponentsId.end()) {
				return false;
			}

			m_ComponentsId[T::GetStaticName()] = nextComponentId++;
			return true;
		}

		void ReserveEntities(uint32_t count)
		{
			m_EntityToBitset.resize(count);
		}

		Entity CreateEntity()
		{
			uint32_t entityId;
			if(m_FreedEntityIds.empty()) {
				entityId = m_NextEntityId++;
				m_EntityToBitset.emplace_back();
			} else {
				entityId = m_FreedEntityIds.back();
				m_FreedEntityIds.pop_back();
				m_EntityToBitset[entityId].reset();
			}
			return { .id = entityId };
		}

		bool HasEntity(Entity entity) const
		{
			return HasEntity(entity.id);
		}

		bool HasEntity(uint32_t entityId) const
		{
			bool isNotFreed = std::find(m_FreedEntityIds.begin(), m_FreedEntityIds.end(), entityId) == m_FreedEntityIds.end();
			bool isNotTooBig = entityId < m_NextEntityId;
			return isNotTooBig && isNotFreed;
		}

		void RemoveEntity(Entity entity)
		{
			RemoveEntity(entity.id);
		}

		void RemoveEntity(uint32_t entityId)
		{
			m_FreedEntityIds.push_back(entityId);
		}

		void RemoveAllEntities()
		{
			m_NextEntityId = 0;
			m_FreedEntityIds.clear();
		}

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename ...Ts>
		bool HasComponents(Entity entity) const;

		template<typename T>
		T& GetComponent(Entity entity);

		template<typename T>
		const T& GetComponent(Entity entity) const;

		template<typename T, typename... Args>
		void AddComponent(Entity entity, Args&&... args);

		template<typename T>
		void RemoveComponent(Entity entity);
	};
};
