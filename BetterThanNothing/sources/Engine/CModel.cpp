#include "CWindow.hpp"
#include "CDevice.hpp"
#include "CSwapChain.hpp"
#include "CVertex.hpp"
#include "CRenderer.hpp"
#include "CModel.hpp"
#include "CTexture.hpp"

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#endif

namespace BetterThanNothing
{
	CModel::CModel(CDevice* pDevice, CRenderer* pRenderer)
		: m_pDevice(pDevice), m_pRenderer(pRenderer)
	{
		m_Position = {0.0f, 0.0f, 0.0f};
		m_Rotation = {0.0f, 0.0f, 0.0f};
		m_Scale	   = 1.0f;
	}

	CModel::~CModel()
	{
		auto device = m_pDevice->GetVkDevice();

		delete m_pTexture;

		vkDestroyBuffer(device, m_IndexBuffer, nullptr);
		vkFreeMemory(device, m_IndexBufferMemory, nullptr);

		vkDestroyBuffer(device, m_VertexBuffer, nullptr);
		vkFreeMemory(device, m_VertexBufferMemory, nullptr);
	}

	void CModel::LoadFromFiles(const std::string& filePath, const std::string& texturePath)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
			throw std::runtime_error(warn + err);
		}

		std::unordered_map<CVertex, uint32_t> uniqueVertices{};

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				CVertex vertex{};

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
					uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertices.size());
					m_Vertices.push_back(vertex);
				}

				m_Indices.push_back(uniqueVertices[vertex]);
			}
		}

		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateTexture(texturePath);
	}

	void CModel::CreateVertexBuffer()
	{
		auto device = m_pDevice->GetVkDevice();
		auto pSwapChain = m_pRenderer->GetSwapChain();

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

	void CModel::CreateIndexBuffer()
	{
		auto device = m_pDevice->GetVkDevice();
		auto pSwapChain = m_pRenderer->GetSwapChain();

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

	void CModel::CreateTexture(const std::string& texturePath)
	{
		m_pTexture = new CTexture(m_pDevice, m_pRenderer->GetCommandPool(), m_pRenderer->GetSwapChain());
		m_pTexture->LoadFromFile(texturePath);
	}
};
