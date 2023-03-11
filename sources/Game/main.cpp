/*
 * File: GameMain.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 10:24:43 am
 * Last Modified: Saturday, 11th March 2023 10:24:45 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>
#include "Core/EngineApp.h"
#include "Game.h"

EngineApp* CreateEngineApplication(void) {
	return new Game("better-than-nothing", 700, 700);
}
