#pragma once

#include "Scene/Component.hpp"
#include "Renderer/Texture.hpp"

struct TextureComponent: public Component {
	Texture texture;
};