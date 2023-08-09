#pragma once

#include <vector>
#include <bitset>

#include "CEntity.hpp"

namespace BetterThanNothing
{
	template<uint32_t ComponentCount, uint32_t SystemCount>
	class CEntityManger
	{
	private:
		std::vector<std::bitset<ComponentCount>>	m_EntitiesBitset;
		std::vector<CEntity>						m_FreedEntities;

	public:
							CEntityManger();
							~CEntityManger();

							CEntityManger(const CEntityManger&) = delete;
		CEntityManger&		operator=(const CEntityManger&) = delete;
							CEntityManger(CEntityManger&&) = delete;
		CEntityManger&		operator=(CEntityManger&&) = delete;

		Entity				CreateEntity();
		void				RemoveEntity(Entity entity);

		template<typename T>
		bool				HasComponent(Entity entity) const;

		template<typename ...Ts>
		bool				HasComponents(Entity entity) const;

		template<typename T>
		T&					GetComponent(Entity entity);

		template<typename T>
		const T&			GetComponent(Entity entity) const;

		template<typename T, typename... Args>
		void				AddComponent(Entity entity, Args&&... args);

		template<typename T>
		void				RemoveComponent(Entity entity);
	};
};
