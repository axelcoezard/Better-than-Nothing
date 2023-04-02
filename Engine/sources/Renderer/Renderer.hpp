#pragma once

#include <vector>

struct Window;

struct Renderer {
private:
	Window*	m_Window;
public:
	explicit Renderer(Window* window);
	~Renderer();

	void Update();
	void Render();
};
