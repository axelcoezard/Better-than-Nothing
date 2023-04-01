#pragma once

#include "Scene/Component.hpp"
#include "Audio/AudioSystem.hpp"

struct AudioComponent: public Component {
	AudioBuffer buffer;
};