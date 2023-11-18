#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* pWindow, Device* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pCommandPool = new CommandPool(m_pDevice);
		m_pSwapChain = new SwapChain(m_pWindow, m_pDevice, m_pCommandPool);
		m_pDescriptorPool = new DescriptorPool(m_pDevice, m_pSwapChain);
		m_pSwapChain->BindDescriptorPool(m_pDescriptorPool);
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_pPipeLines) {
			delete entry.second;
		}

		delete m_pDescriptorPool;
		delete m_pSwapChain;
		delete m_pCommandPool;
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
			m_pSwapChain->CreateNewUniformBuffer();
			m_pDescriptorPool->CreateDescriptorSets(newEntity);
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

			m_pSwapChain->Draw(&globalUniforms, &drawPacket, i);
		}

		m_pSwapChain->EndRecordCommandBuffer();
	}
}