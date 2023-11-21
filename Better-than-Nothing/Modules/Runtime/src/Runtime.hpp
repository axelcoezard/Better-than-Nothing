#pragma once

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	class DrawStreamBuilder;

	class Scene;

	class Event;
	class KeyPressEvent;

	class Runtime: public Application {
	public:
		Runtime() { };

		void OnEnable() override;
		void OnDisable() override;

		static bool OnKeyPress(KeyPressEvent* event);
	};
};
