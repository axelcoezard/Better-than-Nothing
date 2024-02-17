#pragma once

// Application
#include "Application.hpp"
#include "Device.hpp"
#include "Window.hpp"

// Utils
#include "Utils/ConfigManager.hpp"
#include "Utils/Input.hpp"

// Events

#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/WindowCloseEvent.hpp"

// Renderer
#include "Renderer/Renderer.hpp"
#include "Renderer/RendererDebugInfo.hpp"
#include "Renderer/CommandPool.hpp"
#include "Renderer/CommandBuffer.hpp"
#include "Renderer/DescriptorPool.hpp"
#include "Renderer/ImGuiDescriptorPool.hpp"
#include "Renderer/Pipeline.hpp"
#include "Renderer/RenderPass.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Buffer.hpp"

#include "Renderer/DrawStream/DrawStream.hpp"
#include "Renderer/DrawStream/DrawStreamBufferPool.hpp"
#include "Renderer/DrawStream/GlobalData.hpp"
#include "Renderer/DrawStream/MaterialData.hpp"
#include "Renderer/DrawStream/TransformData.hpp"
#include "Renderer/DrawStream/VertexData.hpp"
#include "Renderer/DrawStream/IndexData.hpp"

// Resources
#include "Resources/ResourcePool.hpp"
#include "Resources/ModelPool.hpp"
#include "Resources/Model.hpp"
#include "Resources/TexturePool.hpp"
#include "Resources/Texture.hpp"
#include "Resources/ShaderPool.hpp"
#include "Resources/Shader.hpp"
#include "Resources/ResourceManager.hpp"

// Scene
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Light.hpp"

#include "Scene/Components/ModelComponent.hpp"
#include "Scene/Components/TransformComponent.hpp"
