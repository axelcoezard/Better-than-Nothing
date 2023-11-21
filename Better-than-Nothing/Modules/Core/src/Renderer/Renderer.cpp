#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* window, Device* device): m_Window(window), m_Device(device)
	{
		m_DescriptorPool = new DescriptorPool(m_Device);
		m_SwapChain = new SwapChain(m_Window, m_Device, m_DescriptorPool);

		m_UniformBuffersSize = 0;
		m_UniformBuffersCapacity = 1000;

		m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i].resize(m_UniformBuffersCapacity);
			m_UniformBuffersMemory[i].resize(m_UniformBuffersCapacity);
			m_UniformBuffersMapped[i].resize(m_UniformBuffersCapacity);
		}
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_PipeLines) {
			delete entry.second;
		}

		DestroyUniformBuffers();
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
				m_UniformBuffersMemory[i].resize(m_UniformBuffersCapacity);
				m_UniformBuffersMapped[i].resize(m_UniformBuffersCapacity);
			}
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_Device->CreateBuffer(bufferSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				m_UniformBuffers[i][m_UniformBuffersSize],
				m_UniformBuffersMemory[i][m_UniformBuffersSize]);

			vkMapMemory(m_Device->GetVkDevice(),
				m_UniformBuffersMemory[i][m_UniformBuffersSize], 0,
				bufferSize, 0,
				&m_UniformBuffersMapped[i][m_UniformBuffersSize]);
		}

		m_UniformBuffersSize += 1;
	}

	void Renderer::DestroyUniformBuffers()
	{
		auto device = m_Device->GetVkDevice();

		if (m_UniformBuffers.size() < MAX_FRAMES_IN_FLIGHT || m_UniformBuffersMemory.size() < MAX_FRAMES_IN_FLIGHT) {
			return;
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			for (size_t j = 0; j < m_UniformBuffers[i].size(); j++) {
				if (m_UniformBuffers[i][j] != VK_NULL_HANDLE) {
					vkDestroyBuffer(device, m_UniformBuffers[i][j], nullptr);
				}
			}

			for (size_t j = 0; j < m_UniformBuffersMemory[i].size(); j++) {
				vkFreeMemory(device, m_UniformBuffersMemory[i][j], nullptr);
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

		// Create a new uniform buffer and a new descriptor set for each new entity
		while (scene->HasPendingEntities()) {
			Entity* newEntity = scene->NextPendingEntity();
			CreateNewUniformBuffer();
			m_DescriptorPool->CreateDescriptorSets(newEntity, m_UniformBuffers);
		}

		if (!m_SwapChain->BeginRecordCommandBuffer()) {
			throw std::runtime_error("Failed to record command buffer!");
		}

		// Create a GlobalUniforms with camera data
		GlobalUniforms globalUniforms;
		globalUniforms.projection = scene->GetCamera()->GetProjectionMatrix();
		globalUniforms.view = scene->GetCamera()->GetViewMatrix();
		globalUniforms.cameraPosition = scene->GetCamera()->GetPosition();

		globalUniforms.directionalLight = {
			.color = glm::vec3(1.0f, 1.0f, 1.0f),
			.ambient = 1.0f,
			.diffuse = 0.5f,
			.specular = 0.5f,
			.direction = glm::vec3(0.0f, 0.0f, 0.0f)
		};

		globalUniforms.pointLights.push_back({
			.color = glm::vec3(1.0f, 1.0f, 1.0f),
			.ambient = 0.5f,
			.diffuse = 0.5f,
			.specular = 0.5f,
			.position = glm::vec3(15.0f, 0.0f, 0.0f),
			.constant = 1.0f,
			.linear = 0.09f,
			.quadratic = 0.032f
		});

		globalUniforms.pointLights.push_back({
			.color = glm::vec3(1.0f, 1.0f, 1.0f),
			.ambient = 0.5f,
			.diffuse = 0.5f,
			.specular = 0.5f,
			.position = glm::vec3(2.3f, -3.3f, -4.0f),
			.constant = 1.0f,
			.linear = 0.09f,
			.quadratic = 0.032f
		});

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
		for (u32 i = 0; i < drawStream->size; i++) {
			DrawPacket drawPacket = drawStream->drawPackets[i];

			if (drawPacket.pipeline != currentPipeline) {
				currentPipeline = drawPacket.pipeline;
				m_SwapChain->BindPipeline(static_cast<Pipeline*>(currentPipeline));
			}

			globalUniforms.model = drawPacket.model;

			memcpy(
				m_UniformBuffersMapped[m_SwapChain->GetCurrentFrame()][i],
				&globalUniforms,
				sizeof(globalUniforms));

			m_SwapChain->Draw(&drawPacket, i);
		}

		m_SwapChain->EndRecordCommandBuffer();
	}
}
