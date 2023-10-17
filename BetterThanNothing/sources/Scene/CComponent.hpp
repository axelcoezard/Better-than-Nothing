#pragma once

namespace BetterThanNothing
{
	template<typename T, auto Type>
	class CComponent
	{
	public:
		static constexpr auto type = static_cast<std::size_t>(Type);
	};
};
