/*
 * File: Game.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 1:43:23 pm
 * Last Modified: Saturday, 11th March 2023 1:44:00 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "Core/EngineApp.h"
#include "Events/KeyEvent.h"

class Game: public EngineApp {
	public:
		float vertices[12] = {
			300, 300, 0.0, // top right corner
			0, 300, 0.0, // top left corner
			0, 0, 0.0, // bottom left corner
			300, 0, 0.0 // bottom right corner
		};

		Game(std::string_view title, uint32_t width, uint32_t height)
			: EngineApp(title, width, height) {};

		void OnEnable(void);
		void OnDisable(void);
		void OnEvent(Event* event);
		void OnUpdate(void);
		void OnRender(Renderer* renderer);

		static bool OnKeyPress(KeyPressEvent* event);
};
