/*
 * File: main.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 6:00:12 pm
 * Last Modified: Tuesday, 7th March 2023 9:49:41 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/GarbageCollector/GarbageCollector.h"
#include "Core/EngineApp.h"

extern EngineApp* CreateEngineApplication(void);

int main(void) {
	EngineApp* app = CreateEngineApplication();
	app->Run();
	GarbageCollector::Destroy();
	return 0;
}
