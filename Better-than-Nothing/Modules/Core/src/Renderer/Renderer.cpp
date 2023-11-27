#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* window, Device* device): m_Window(window), m_Device(device)
	{
		m_UniformPool = new UniformsPool(m_Device);
		m_DescriptorPool = new DescriptorPool(m_Device);
		m_SwapChain = new SwapChain(m_Window, m_Device, m_DescriptorPool);

		m_UniformBuffersSize = 0;
		m_UniformBuffersCapacity = 1000;

		m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i].resize(m_UniformBuffersCapacity);
		}
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_PipeLines) {
			delete entry.second;
		}

		DestroyUniformBuffers();
		delete m_UniformPool;
		delete m_DescriptorPool;
		delete m_SwapChain;
	}

	void Renderer::CreateNewUniformBuffer()
	{
		VkDeviceSize bufferSize = sizeof(GlobalUniforms);

		if (m_UniformBuffersSize >= m_UniformBuffersCapacity) {
			m_UniformBuffersCapacity *= 2;

			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				m_UniformBuffers[i].resize(m_UniformBuffersCapacity);
			}
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_Device->CreateBuffer(
				&m_UniformBuffers[i][m_UniformBuffersSize],
				bufferSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(
				&m_UniformBuffers[i][m_UniformBuffersSize],
				0, 0,
				&m_UniformBuffers[i][m_UniformBuffersSize].m_Mapped);
		}

		m_UniformBuffersSize += 1;
	}

	void Renderer::DestroyUniformBuffers()
	{
		if (m_UniformBuffers.size() < MAX_FRAMES_IN_FLIGHT) {
			return;
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			for (size_t j = 0; j < m_UniformBuffers[i].size(); j++) {
				m_Device->DestroyBuffer(&m_UniformBuffers[i][j]);
			}
		}
	}

	void Renderer::LoadPipeline(const std::string& id, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		const std::string& basePath = "/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Shaders/";
		auto pipeline = new Pipeline(id, m_Device, m_SwapChain, m_DescriptorPool, basePath + vertexShaderFilePath, basePath + fragmentShaderFilePath);
		auto entry = std::pair<std::string, Pipeline*>(id, pipeline);

		m_PipeLines.insert(entry);
	}

	void Renderer::Render(Scene* scene)
	{
		Pipeline* pPipeline = m_PipeLines.at("main");
		u32 currentFrame = m_SwapChain->GetCurrentFrame();

		// Create a new uniform buffer and a new descriptor set for each new entity
		while (scene->HasPendingEntities()) {
			Entity* newEntity = scene->NextPendingEntity();

			//CreateNewUniformBuffer();
			if (m_UniformPool->ShouldExtends()) {
				m_UniformPool->ExtendUniformsPool();
			}
			std::vector<Buffer*> newGU = m_UniformPool->GetAllGlobalUniforms();
			std::vector<Buffer*> newDU = m_UniformPool->CreateDynamicUniforms();
			m_DescriptorPool->CreateDescriptorSets(newEntity, newGU, newDU);
		}

		if (!m_SwapChain->BeginRecordCommandBuffer()) {
			throw std::runtime_error("Failed to record command buffer!");
		}

		// Create a GlobalUniforms with camera data
		GlobalUniforms* globalUniforms = m_UniformPool->GetGlobalUniforms(currentFrame);
		globalUniforms->projection = scene->GetCamera()->GetProjectionMatrix();
		globalUniforms->view = scene->GetCamera()->GetViewMatrix();
		globalUniforms->cameraPosition = scene->GetCamera()->GetPosition();
		globalUniforms->directionalLight = {
			.color = glm::vec3(1.0f, 1.0f, 1.0f),
			.direction = glm::vec3(-1.0f, 0.0f, -1.0f)
		};

		// Append all the usefull Model's data to create a sorted DrawStream
		DrawStreamBuilder drawStreamBuilder(scene->GetEntities().size());
		for (auto & entity : scene->GetEntities()) {
			Model* model = entity->GetModel();

			drawStreamBuilder.Draw({
				.pipeline = pPipeline,
				.texture = entity->GetTexture(),
				.vertexBuffer = model->vertexBuffer,
				.indexBuffer = model->indexBuffer,
				.indicesCount = model->indexCount,
				.model = entity->GetModelMatrix()
			});
		}

		DrawStream* drawStream = drawStreamBuilder.GetStream();
		void* currentPipeline = nullptr;

		// Draw all the DrawPacket in the DrawStream ordered by pipeline
		// and bind the pipeline only when it changes
		// TODO: Use multiple threads to draw the DrawStream
		for (u32 i = 0; i < drawStream->size; i++) {
			DrawPacket drawPacket = drawStream->drawPackets[i];

			if (drawPacket.pipeline != currentPipeline) {
				currentPipeline = drawPacket.pipeline;
				m_SwapChain->BindPipeline(static_cast<Pipeline*>(currentPipeline));
			}

			DynamicUniforms* dynamicUniforms = m_UniformPool->GetDynamicUniforms(currentFrame, i);
			dynamicUniforms->model = drawPacket.model;
			dynamicUniforms->material = { 0.5f, 0.1f, 0.5f, 1.0f };

			m_SwapChain->Draw(&drawPacket, i);
		}

		m_SwapChain->EndRecordCommandBuffer();
	}
}
