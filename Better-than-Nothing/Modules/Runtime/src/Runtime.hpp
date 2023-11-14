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
		Runtime(std::string_view title, u32 width, u32 height)
			: Application(title, width, height) { };

		void OnEnable() override;
		void OnDisable() override;

		static bool OnKeyPress(KeyPressEvent* event);
	};
};
