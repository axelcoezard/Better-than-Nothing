#pragma once

namespace BetterThanNothing
{
	class CDevice;
	class CRenderer;
	class CVertex;

	class CModel
	{
	private:
		CDevice*						m_pDevice;
		CRenderer*						m_pRenderer;

		std::vector<CVertex>			m_Vertices;
		std::vector<uint32_t>			m_Indices;

		VkBuffer						m_VertexBuffer;
		VkDeviceMemory					m_VertexBufferMemory;
		VkBuffer						m_IndexBuffer;
		VkDeviceMemory					m_IndexBufferMemory;

		CTexture*						m_pTexture;

		glm::vec3						m_Position;
		glm::vec3						m_Rotation;
		float							m_Scale;

	public:
										CModel(CDevice* pDevice, CRenderer* pRenderer);
										~CModel();

										CModel(const CModel&) = delete;
		CModel&							operator=(const CModel&) = delete;
										CModel(CModel&&) = delete;
		CModel&							operator=(CModel&&) = delete;

		void							LoadFromFiles(const std::string& filePath, const std::string& texturePath);
		void							Bind(VkCommandBuffer commandBuffer);
		void							Draw(VkCommandBuffer commandBuffer);

	private:
		void							CreateVertexBuffer();
		void							CreateIndexBuffer();
		void							CreateTexture(const std::string& texturePath);

	public:
		VkBuffer&						GetVertexBuffer() { return m_VertexBuffer; }
		VkBuffer&						GetIndexBuffer() { return m_IndexBuffer; }
		uint32_t						GetIndicesCount() { return static_cast<uint32_t>(m_Indices.size()); }
		CTexture*						GetTexture() { return m_pTexture; }

		glm::vec3&						GetPosition() { return m_Position; }
		glm::vec3&						GetRotation() { return m_Rotation; }
		float&							GetScale() { return m_Scale; }

		void							SetPosition(const glm::vec3& position) { m_Position = position; }
		void							SetPosition(float x, float y, float z) { m_Position = {x, y, z}; }
		void							SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		void							SetRotation(float x, float y, float z) { m_Rotation = {x, y, z}; }
		void							SetScale(float scale) { m_Scale = scale; }
	};
};
