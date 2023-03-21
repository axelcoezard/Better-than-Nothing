/*
 * File: Game.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 9:46:02 am
 * Last Modified: Saturday, 11th March 2023 9:46:04 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <iostream>

#include "Core/Window.h"
#include "Core/Renderer.h"

class EngineApp {
	protected:
		Window* m_Window;
		Renderer* m_Renderer;
	public:
		EngineApp(std::string_view title, uint32_t width, uint32_t height);
		virtual ~EngineApp(void) = default;

		void Run(void);

		virtual void OnEnable(void) = 0;
		virtual void OnDisable(void) = 0;
		virtual void OnEvent(Event* event) = 0;
		virtual void OnUpdate(void) = 0;
		virtual void OnRender(Renderer* renderer) = 0;
};
