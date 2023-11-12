#pragma once

#include "Application.hpp"

namespace BetterThanNothing
{
	class Event;
	class Renderer;
	class Scene;
	class KeyPressEvent;

	class Sandbox: public Application {
	public:
		Sandbox(std::string_view title, uint32_t width, uint32_t height)
			: Application(title, width, height) { };

		void OnEnable() override;
		void OnDisable() override;
		void OnEvent(Event* event) override;
		void OnUpdate(float deltatime) override;
		void OnRender(Renderer* renderer) override;

		static bool OnKeyPress(KeyPressEvent* event);
	};
};
