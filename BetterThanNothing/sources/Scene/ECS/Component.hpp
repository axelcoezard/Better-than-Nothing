#pragma once

namespace BetterThanNothing
{
	struct Component
	{
		#define COMPONENT_NAME(name)\
			static const char* GetStaticName() { return #name; }\
			virtual const char* GetName() const override { return GetStaticName(); }

		[[nodiscard]] virtual const char* GetName() const = 0;
	};
};
