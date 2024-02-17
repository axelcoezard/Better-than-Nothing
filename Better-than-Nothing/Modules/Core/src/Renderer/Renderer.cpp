#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* window, Device* device, ResourceManager* resourceManager)
		: m_Window(window), m_Device(device), m_ResourceManager(resourceManager)
	{
		m_UniformsPool = new UniformsPool(m_Device);
		m_DescriptorPool = new DescriptorPool(m_Device);
		m_SwapChain = new SwapChain(m_Window, m_Device, m_DescriptorPool);
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_PipeLines) {
			delete entry.second;
		}

		delete m_UniformsPool;
		delete m_DescriptorPool;
		delete m_SwapChain;
	}

	void Renderer::LoadPipeline(const std::string& id, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		Pipeline* pipeline = new Pipeline(id, m_Device, m_SwapChain, m_DescriptorPool);
		Shader* vertexShader = m_ResourceManager->GetShader(vertexShaderFilePath);
		Shader* fragmentShader = m_ResourceManager->GetShader(fragmentShaderFilePath);

		pipeline->CreateGraphicsPipeline(vertexShader, fragmentShader);

		m_PipeLines.insert(std::pair<std::string, Pipeline*>(id, pipeline));
	}

	void Renderer::Render(Scene* scene, RendererDebugInfo* debugInfo)
	{
		Pipeline* pPipeline = m_PipeLines.at("main");
		u32 currentFrame = m_SwapChain->GetCurrentFrame();

		// Create a new uniform buffer and a new descriptor set for each new entity
		while (scene->HasPendingEntities())
		{
			Entity newEntity = scene->NextPendingEntity();

			if (m_UniformsPool->ShouldExtends())
				m_UniformsPool->ExtendUniformsPool();

			std::vector<Buffer*> newGU = m_UniformsPool->GetAllGlobalUniforms();
			std::vector<Buffer*> newDU = m_UniformsPool->CreateDynamicUniforms();

			std::cout << "newGU size: " << newGU.size() << std::endl;
			std::cout << "newDU size: " << newDU.size() << std::endl;

			ModelComponent modelComp = scene->GetComponent<ModelComponent>(newEntity);

			DescriptorLayout globalUniformsLayout = m_DescriptorPool->FindDescriptorLayoutByName("globalUniforms");
			u32 guIndex = m_DescriptorPool->CreateDescriptor(globalUniformsLayout.m_Id);

			std::cout << "globalUniforms: " << globalUniformsLayout.m_LayoutInfo.name << " | binding: " << globalUniformsLayout.m_LayoutInfo.binding <<  std::endl;
			std::cout << "guIndex: " << guIndex << std::endl;

			DescriptorLayout dynamicUniformsLayout = m_DescriptorPool->FindDescriptorLayoutByName("dynamicUniforms");
			u32 duIndex = m_DescriptorPool->CreateDescriptor(globalUniformsLayout.m_Id);

			std::cout << "dynamicUniforms: " << dynamicUniformsLayout.m_LayoutInfo.name << " | binding: " << dynamicUniformsLayout.m_LayoutInfo.binding <<  std::endl;
			std::cout << "duIndex: " << duIndex << std::endl;

			DescriptorLayout samplerLayout = m_DescriptorPool->FindDescriptorLayoutByName("texSampler");
			u32 samplerIndex = m_DescriptorPool->CreateDescriptor(samplerLayout.m_Id);

			std::cout << "sampler: " << samplerLayout.m_LayoutInfo.name << " | binding: " << samplerLayout.m_LayoutInfo.binding <<  std::endl;
			std::cout << "samplerIndex: " << samplerIndex << std::endl;

			for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				VkDescriptorBufferInfo bufferInfo = { .buffer = newGU[i]->m_Buffer, .offset = 0, .range = sizeof(GlobalUniforms) };
				m_DescriptorPool->GetDescriptors(i)[guIndex].Update(
					globalUniformsLayout.m_LayoutInfo.binding,
					globalUniformsLayout.m_LayoutInfo.descriptorType,
					&bufferInfo,
					nullptr
				);
			}

			for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				VkDescriptorBufferInfo bufferInfo = { .buffer = newDU[i]->m_Buffer, .offset = 0, .range = sizeof(DynamicUniforms) };
				m_DescriptorPool->GetDescriptors(i)[duIndex].Update(
					dynamicUniformsLayout.m_LayoutInfo.binding,
					dynamicUniformsLayout.m_LayoutInfo.descriptorType,
					&bufferInfo,
					nullptr
				);
			}

			for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			{
				VkDescriptorImageInfo imageInfo = { .sampler = modelComp.texture->sampler, .imageView = modelComp.texture->imageView, .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
				m_DescriptorPool->GetDescriptors(i)[samplerIndex].Update(
					samplerLayout.m_LayoutInfo.binding,
					samplerLayout.m_LayoutInfo.descriptorType,
					nullptr,
					&imageInfo
				);
			}

			exit(1);
		}

		RenderDebugInfo(debugInfo);

		if (!m_SwapChain->BeginRecordCommandBuffer())
			throw std::runtime_error("Failed to record command buffer!");

		// Create a GlobalUniforms with camera data
		GlobalUniforms* globalUniforms = m_UniformsPool->GetGlobalUniforms(currentFrame);
		globalUniforms->projection = scene->GetCamera()->GetProjectionMatrix();
		globalUniforms->view = scene->GetCamera()->GetViewMatrix();
		globalUniforms->cameraPosition = scene->GetCamera()->GetPosition();
		globalUniforms->directionalLight = {
			.color = glm::vec3(1.0f, 1.0f, 1.0f),
			.direction = glm::vec3(-1.0f, 0.0f, -1.0f)
		};

		// Append all the usefull Model's data to create a sorted DrawStream
		DrawStreamBuilder drawStreamBuilder(scene->GetEntitiesCount());
		auto view = scene->GetView<ModelComponent, TransformComponent>();
		for (auto entity : view)
		{
			ModelComponent& modelComp = view.get<ModelComponent>(entity);
			TransformComponent& transformComp = view.get<TransformComponent>(entity);

			drawStreamBuilder.Draw({
				.pipeline = pPipeline,
				.texture = modelComp.texture,
				.vertexBuffer = modelComp.model->vertexBuffer,
				.indexBuffer = modelComp.model->indexBuffer,
				.indicesCount = modelComp.model->indexCount,
				.model = TransformComponent::GetModelMatrix(transformComp)
			});
		};

		DrawStream* drawStream = drawStreamBuilder.GetStream();
		void* currentPipeline = nullptr;

		// Draw all the DrawPacket in the DrawStream ordered by pipeline
		// and bind the pipeline only when it changes
		// TODO: Use multiple threads to draw the DrawStream
		for (u32 i = 0; i < drawStream->size; i++)
		{
			DrawPacket drawPacket = drawStream->drawPackets[i];

			if (drawPacket.pipeline != currentPipeline)
			{
				currentPipeline = drawPacket.pipeline;
				m_SwapChain->BindPipeline(static_cast<Pipeline*>(currentPipeline));
			}

			DynamicUniforms* dynamicUniforms = m_UniformsPool->GetDynamicUniforms(currentFrame, i);
			dynamicUniforms->model = drawPacket.model;
			dynamicUniforms->material = { 0.5f, 0.1f, 0.5f, 1.0f };

			m_SwapChain->Draw(&drawPacket, i);
		}

		m_SwapChain->EndRecordCommandBuffer();
	}

	void Renderer::RenderDebugInfo(RendererDebugInfo* debugInfo)
	{
		(void) debugInfo;
#if ENABLE_IMGUI
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(350, 200), 0);

		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoResize;

		ImGui::Begin("Debug", nullptr, windowFlags);

		ImGui::Text("Vendor: %s", debugInfo->vendorName.c_str());
		ImGui::Text("Device: %s", debugInfo->deviceName.c_str());
		ImGui::Text("API: %s", debugInfo->apiVersion.c_str());

		ImGui::Separator();

		ImGui::Text("Frame: %d", debugInfo->frameCount);
		ImGui::Text("Frame time: %f ms", debugInfo->frameTime * 1000);
		ImGui::Text("Frame per second (fps): %f fps", 1.0f / debugInfo->frameTime);

		ImGui::Separator();

		ImGui::Text("Scene: %s", debugInfo->sceneName.c_str());
		ImGui::Text("Entities: %d", debugInfo->sceneEntitiesCount);

		ImGui::End();

		ImGui::Render();
#endif
	}
}
