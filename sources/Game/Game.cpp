/*
 * File: Game.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 1:45:15 pm
 * Last Modified: Saturday, 11th March 2023 1:45:24 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Game.h"
#include "Events/EventDispatcher.h"

void Game::OnEnable(void) {
	//glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	//glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	//glOrtho( 0, m_Window->GetWidth(), 0, m_Window->GetHeight(), 0, 1 ); // essentially set coordinate system
	//glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	//glLoadIdentity( ); // same as above comment
}

void Game::OnDisable(void) {

}

void Game::OnEvent(Event* event) {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressEvent>(Game::OnKeyPress);
}

bool Game::OnKeyPress(KeyPressEvent* event) {
	std::cout << event->GetName() << " => " << event->GetKey() << std::endl;
	return true;
}

void Game::OnUpdate(void) {

}

void Game::OnRender(Renderer* renderer) {
	glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
	glVertexPointer( 3, GL_FLOAT, 0, vertices ); // point to the vertices to be used
	glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
	glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL
	(void) renderer;
}

EngineApp* CreateEngineApplication(void) {
	return new Game("better-than-nothing", 700, 700);
}
