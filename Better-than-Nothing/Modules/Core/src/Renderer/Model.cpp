#include "Renderer/Window.hpp"
#include "Renderer/Device.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/Vertex.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/Texture.hpp"

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#endif

namespace BetterThanNothing
{
	Model::Model()
	{
		m_Position = {0.0f, 0.0f, 0.0f};
		m_Rotation = {0.0f, 0.0f, 0.0f};
		m_Scale	   = 1.0f;
	}

	Model::~Model()
	{
		//auto device = m_pDevice->GetVkDevice();

		///delete m_pTexture;

		//vkDestroyBuffer(device, m_IndexBuffer, nullptr);
		//vkFreeMemory(device, m_IndexBufferMemory, nullptr);

		//vkDestroyBuffer(device, m_VertexBuffer, nullptr);
		//vkFreeMemory(device, m_VertexBufferMemory, nullptr);
	}

	void Model::LoadFromFiles(const std::string& filePath, const std::string& texturePath)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
			throw std::runtime_error(warn + err);
		}

		std::unordered_map<Vertex, u32> uniqueVertices{};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex{};

				vertex.m_Position = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.m_TextureCoordinates = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.m_Color = {1.0f, 1.0f, 1.0f};

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<u32>(m_Vertices.size());
					m_Vertices.push_back(vertex);
				}

				m_Indices.push_back(uniqueVertices[vertex]);
			}
		}

		m_TexturePath = texturePath;
	}

	void Model::CreateVertexBuffer(Device* pDevice, Renderer* pRenderer)
	{
		auto device = pDevice->GetVkDevice();
		auto pSwapChain = pRenderer->GetSwapChain();

		VkDeviceSize bufferSize = sizeof(m_Vertices[0]) * m_Vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		pSwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, m_Vertices.data(), (size_t) bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		pSwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_VertexBuffer,
			m_VertexBufferMemory);

		pSwapChain->CopyBuffer(stagingBuffer, m_VertexBuffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);
	}

	void Model::CreateIndexBuffer(Device* pDevice, Renderer* pRenderer)
	{
		auto device = pDevice->GetVkDevice();
		auto pSwapChain = pRenderer->GetSwapChain();

		VkDeviceSize bufferSize = sizeof(m_Indices[0]) * m_Indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		pSwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, m_Indices.data(), (size_t) bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		pSwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_IndexBuffer,
			m_IndexBufferMemory);

		pSwapChain->CopyBuffer(stagingBuffer, m_IndexBuffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);
	}

	void Model::CreateTexture(Device* pDevice, Renderer* pRenderer)
	{
		m_pTexture = new Texture(pDevice, pRenderer->GetCommandPool(), pRenderer->GetSwapChain());
		m_pTexture->LoadFromFile(m_TexturePath);
	}

	glm::mat4 Model::GetModelMatrix()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(m_Scale));
		model = glm::translate(model, m_Position);
		model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return model;
	}
};
