/*
 * File: Game.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 1:45:15 pm
 * Last Modified: Saturday, 11th March 2023 1:45:24 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Game.h"

Game::Game(std::string_view title, uint32_t width, uint32_t height)
	: EngineApp(title, width, height) {}

void Game::OnEnable(void) {

}

void Game::OnDisable(void) {

}

void Game::OnEvent(EventDispatcher* dispatcher, Event* event) {
	(void) dispatcher;
	std::cout << event->GetName() << std::endl;
}

void Game::OnUpdate(void) {

}

void Game::OnRender(void) {

}
