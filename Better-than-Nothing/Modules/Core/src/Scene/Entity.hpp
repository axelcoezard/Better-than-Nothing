#pragma once

namespace BetterThanNothing
{
	class Model;
	class Texture;

	class Entity
	{
	private:
		glm::vec3						m_Position;
		glm::vec3						m_Rotation;
		f32								m_Scale;

		Model*							m_Model;
		Texture*						m_Texture;

	public:
										Entity();
										~Entity();

										Entity(const Entity&) = delete;
		Entity&							operator=(const Entity&) = delete;
										Entity(Entity&&) = delete;
		Entity&							operator=(Entity&&) = delete;

		void							UseModel(Model* model) { m_Model = model; }
		void							UseTexture(Texture* texture) { m_Texture = texture; }

		glm::vec3&						GetPosition() { return m_Position; }
		glm::vec3&						GetRotation() { return m_Rotation; }
		f32&							GetScale() { return m_Scale; }

		glm::mat4						GetModelMatrix();

		Model*							GetModel() { return m_Model; }
		Texture*						GetTexture() { return m_Texture; }

		void							SetPosition(const glm::vec3& position) { m_Position = position; }
		void							SetPosition(f32 x, f32 y, f32 z) { m_Position = {x, y, z}; }
		void							SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
		void							SetRotation(f32 x, f32 y, f32 z) { m_Rotation = {x, y, z}; }
		void							SetScale(f32 scale) { m_Scale = scale; }
	};
};
