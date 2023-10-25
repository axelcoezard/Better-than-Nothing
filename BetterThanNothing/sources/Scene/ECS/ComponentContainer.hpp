#pragma once

namespace BetterThanNothing
{
	template<typename T>
	class ComponentContainer
	{
	private:
		std::vector<T>	m_EntityToComponents;
	};
};
