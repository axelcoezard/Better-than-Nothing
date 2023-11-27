#pragma once

// Application
#include "Application.hpp"

// Utils
#include "Utils/ConfigManager.hpp"

// Events

#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/WindowCloseEvent.hpp"

// Renderer

#include "Renderer/Device.hpp"
#include "Renderer/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/CommandPool.hpp"
#include "Renderer/CommandBuffer.hpp"
#include "Renderer/DescriptorPool.hpp"
#include "Renderer/Device.hpp"
#include "Renderer/Pipeline.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/GlobalUniforms.hpp"
#include "Renderer/UniformsPool.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/DrawStream.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Buffer.hpp"

// Ressources
#include "Ressources/RessourcePool.hpp"
#include "Ressources/Model.hpp"
#include "Ressources/Texture.hpp"

// Scene

#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Light.hpp"

#include "Scene/Components/ModelComponent.hpp"
#include "Scene/Components/TransformComponent.hpp"
