#pragma once

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	class Event;
	class Renderer;
	class Scene;
	class KeyPressEvent;

	class Sandbox: public Application {
	public:
		Sandbox(std::string_view title, u32 width, u32 height)
			: Application(title, width, height) { };

		void OnEnable() override;
		void OnDisable() override;
		void OnEvent(Event* event) override;
		void OnUpdate(f32 deltatime) override;
		void OnRender(Renderer* renderer) override;

		static bool OnKeyPress(KeyPressEvent* event);
	};
};
