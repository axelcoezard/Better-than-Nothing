#pragma once

#include <vector>

struct Window;

struct Renderer {
private:
	Window*	m_Window;
public:
	Renderer(Window* window);
	~Renderer(void);

	void Update(void);
	void Render(void);
};
