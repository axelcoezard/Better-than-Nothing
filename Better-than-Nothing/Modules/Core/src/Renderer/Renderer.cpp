#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* window, Device* device): m_Window(window), m_Device(device)
	{
		m_UniformsPool = new UniformsPool(m_Device);
		m_DescriptorPool = new DescriptorPool(m_Device, m_UniformsPool);
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
			Entity newEntity = scene->NextPendingEntity();

			if (m_UniformsPool->ShouldExtends()) {
				m_UniformsPool->ExtendUniformsPool();
			}
			std::vector<Buffer*> newGU = m_UniformsPool->GetAllGlobalUniforms();
			std::vector<Buffer*> newDU = m_UniformsPool->CreateDynamicUniforms();

			ModelComponent modelComp = scene->GetComponent<ModelComponent>(newEntity);
			m_DescriptorPool->CreateDescriptorSets(&modelComp, newGU, newDU);
		}

		if (!m_SwapChain->BeginRecordCommandBuffer()) {
			throw std::runtime_error("Failed to record command buffer!");
		}

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
		for (auto entity : view) {
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
		for (u32 i = 0; i < drawStream->size; i++) {
			DrawPacket drawPacket = drawStream->drawPackets[i];

			if (drawPacket.pipeline != currentPipeline) {
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
}
