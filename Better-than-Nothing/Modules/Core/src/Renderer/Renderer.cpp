#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* pWindow, Device* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pDescriptorPool = new DescriptorPool(m_pDevice);
		m_pSwapChain = new SwapChain(m_pWindow, m_pDevice, m_pDescriptorPool);

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
		for (auto & entry : m_pPipeLines) {
			delete entry.second;
		}

		DestroyUniformBuffers();
		delete m_pDescriptorPool;
		delete m_pSwapChain;
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
			m_pDevice->CreateBuffer(bufferSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				m_UniformBuffers[i][m_UniformBuffersSize],
				m_UniformBuffersMemory[i][m_UniformBuffersSize]);

			vkMapMemory(m_pDevice->GetVkDevice(),
				m_UniformBuffersMemory[i][m_UniformBuffersSize], 0,
				bufferSize, 0,
				&m_UniformBuffersMapped[i][m_UniformBuffersSize]);
		}

		m_UniformBuffersSize += 1;
	}

	void Renderer::DestroyUniformBuffers()
	{
		auto device = m_pDevice->GetVkDevice();

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
		auto pipeline = new Pipeline(id, m_pDevice, m_pSwapChain, m_pDescriptorPool, vertexShaderFilePath, fragmentShaderFilePath);
		auto entry = std::pair<std::string, Pipeline*>(id, pipeline);

		m_pPipeLines.insert(entry);
	}

	void Renderer::Render(Scene* pScene)
	{
		Pipeline* pPipeline = m_pPipeLines.at("main");

		// Create a new uniform buffer and a new descriptor set for each new entity
		while (pScene->HasPendingEntities()) {
			Entity* newEntity = pScene->NextPendingEntity();
			CreateNewUniformBuffer();
			m_pDescriptorPool->CreateDescriptorSets(newEntity, m_UniformBuffers);
		}

		if (!m_pSwapChain->BeginRecordCommandBuffer()) {
			throw std::runtime_error("Failed to record command buffer!");
		}

		// Create a GlobalUniforms with camera data
		GlobalUniforms globalUniforms;
		globalUniforms.projection = pScene->GetCamera()->GetProjectionMatrix();
		globalUniforms.view = pScene->GetCamera()->GetViewMatrix();

		// Append all the usefull Model's data to create a sorted DrawStream
		DrawStreamBuilder drawStreamBuilder(pScene->GetEntities().size());
		for (auto & entity : pScene->GetEntities()) {
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
				m_pSwapChain->BindPipeline(static_cast<Pipeline*>(currentPipeline));
			}

			globalUniforms.model = drawPacket.model;

			u32 currentFrame = m_pSwapChain->GetCurrentFrame();
			memcpy(m_UniformBuffersMapped[currentFrame][i], &globalUniforms, sizeof(globalUniforms));

			m_pSwapChain->Draw(&drawPacket, i);
		}

		m_pSwapChain->EndRecordCommandBuffer();
	}
}
