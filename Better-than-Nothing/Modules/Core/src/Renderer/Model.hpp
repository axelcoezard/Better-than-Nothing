#pragma once

namespace BetterThanNothing
{
	class Device;
	class Renderer;
	class Vertex;
	class Texture;

	class Model
	{
	private:
		std::vector<Vertex>				m_Vertices;
		std::vector<u32>				m_Indices;

		VkBuffer						m_VertexBuffer;
		VkDeviceMemory					m_VertexBufferMemory;
		VkBuffer						m_IndexBuffer;
		VkDeviceMemory					m_IndexBufferMemory;

		std::string						m_TexturePath;
		Texture*						m_pTexture;

		glm::vec3						m_Position;
		glm::vec3						m_Rotation;
		f32								m_Scale;

	public:
										Model();
										~Model();

										Model(const Model&) = delete;
		Model&							operator=(const Model&) = delete;
										Model(Model&&) = delete;
		Model&							operator=(Model&&) = delete;

		void							LoadFromFiles(const std::string& filePath, const std::string& texturePath);

		void							CreateVertexBuffer(Device* pDevice, Renderer* pRenderer);
		void							CreateIndexBuffer(Device* pDevice, Renderer* pRenderer);
		void							CreateTexture(Device* pDevice, Renderer* pRenderer);

		VkBuffer&						GetVertexBuffer() { return m_VertexBuffer; }
		VkDeviceMemory&					GetVertexBufferMemory() { return m_VertexBufferMemory; }
		VkBuffer&						GetIndexBuffer() { return m_IndexBuffer; }
		VkDeviceMemory&					GetIndexBufferMemory() { return m_IndexBufferMemory; }
		u32								GetIndicesCount() { return static_cast<u32>(m_Indices.size()); }
		Texture*						GetTexture() { return m_pTexture; }

		glm::vec3&						GetPosition() { return m_Position; }
		glm::vec3&						GetRotation() { return m_Rotation; }
		f32&							GetScale() { return m_Scale; }
		glm::mat4						GetModelMatrix();

		void							SetPosition(const glm::vec3& position) { m_Position = position; }
		void							SetPosition(f32 x, f32 y, f32 z) { m_Position = {x, y, z}; }
		void							SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		void							SetRotation(f32 x, f32 y, f32 z) { m_Rotation = {x, y, z}; }
		void							SetScale(f32 scale) { m_Scale = scale; }
	};
};
