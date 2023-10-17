#pragma once

#include "CEntity.hpp"

namespace BetterThanNothing
{
	class CScene
	{
	public:
		CScene() = default;
		~CScene() = default;

	public:
		CEntity CreateEntity();
	};
};
