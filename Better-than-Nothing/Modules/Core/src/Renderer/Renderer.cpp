#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* window, Device* device, ResourceManager* resourceManager)
		: m_Window(window), m_Device(device), m_ResourceManager(resourceManager)
	{
		m_DrawStreamBuffers = new DrawStreamBufferPool(m_Device);
		m_DescriptorPool = new DescriptorPool(m_Device, m_DrawStreamBuffers);
		m_SwapChain = new SwapChain(m_Window, m_Device, m_DescriptorPool);
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_PipeLines) {
			delete entry.second;
		}

		delete m_DrawStreamBuffers;
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
		// Generate all uniform buffer for global data (one for each frame)
		m_DrawStreamBuffers->AllocateAllGlobalData();

		// Generate all storage buffer for vertices and indices (one for each frame and pipeline)
		m_DrawStreamBuffers->AllocateAllVertexAndIndexData(m_PipeLines.size());
	}

	void Renderer::Render(Scene* scene, RendererDebugInfo* debugInfo)
	{
		Pipeline* pPipeline = m_PipeLines.at("main");
		u32 currentFrame = m_SwapChain->GetCurrentFrame();

		// Create a new uniform buffer and a new descriptor set for each new entity
		while (scene->HasPendingEntities())
		{
			Entity newEntity = scene->NextPendingEntity();

			std::vector<Buffer*> allGlobalData = m_DrawStreamBuffers->GetAllGlobalData();

			std::vector<Buffer*> allVertexData = m_DrawStreamBuffers->GetAllVertexData(0);
			std::vector<Buffer*> allIndexData = m_DrawStreamBuffers->GetAllIndexData(0);

			std::vector<Buffer*> newMaterialData = m_DrawStreamBuffers->CreateMaterialData();
			std::vector<Buffer*> newTransformData = m_DrawStreamBuffers->CreateTransformData();

			ModelComponent modelComp = scene->GetComponent<ModelComponent>(newEntity);
			m_DescriptorPool->CreateDescriptorSets(&modelComp, allGlobalData, allVertexData, allIndexData, newMaterialData, newTransformData);
		}

		RenderDebugInfo(debugInfo);
		debugInfo->drawCalls = 0;

		if (!m_SwapChain->BeginRecordCommandBuffer()) {
			throw std::runtime_error("Failed to record command buffer!");
		}

		// Create a GlobalUniforms with camera data
		GlobalData* globalUniforms = m_DrawStreamBuffers->GetGlobalData(currentFrame);
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
		for (auto entity : view) {
			ModelComponent& modelComp = view.get<ModelComponent>(entity);
			TransformComponent& transformComp = view.get<TransformComponent>(entity);

			drawStreamBuilder.Draw({
				.pipeline = pPipeline,
				.texture = modelComp.texture,
				.vertexBuffer = modelComp.model->vertexBuffer,
				.vertexCount = modelComp.model->vertexCount,
				.indexBuffer = modelComp.model->indexBuffer,
				.indicesCount = modelComp.model->indexCount,
				.model = TransformComponent::GetModelMatrix(transformComp)
			});
		};

		std::vector<DrawStream>& drawStream = drawStreamBuilder.GetStreams();

		for (u32 i = 0; i < drawStream.size(); i++)
		{
			DrawStream& currentDrawStream = drawStream.at(i);

			m_SwapChain->BindPipeline(static_cast<Pipeline*>(currentDrawStream.pipeline));

			//DynamicUniforms* dynamicUniforms = m_UniformsPool->GetDynamicUniforms(currentFrame, i);
			//dynamicUniforms->model = drawPacket.model;
			//dynamicUniforms->material = { 0.5f, 0.1f, 0.5f, 1.0f };

			//m_SwapChain->Draw(&drawPacket, i);

			debugInfo->drawCalls++;
			debugInfo->totalDrawCalls++;
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

		ImGui::SetNextWindowSize(ImVec2(350, 250), 0);

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

		ImGui::Text("Draw calls (per frame): %d", debugInfo->drawCalls);
		ImGui::Text("Total draw calls: %d", debugInfo->totalDrawCalls);

		ImGui::Separator();

		ImGui::Text("Scene: %s", debugInfo->sceneName.c_str());
		ImGui::Text("Entities: %d", debugInfo->sceneEntitiesCount);

		ImGui::End();

		ImGui::Render();
#endif
	}
}
