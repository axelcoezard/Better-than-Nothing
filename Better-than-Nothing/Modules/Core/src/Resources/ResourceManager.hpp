#pragma once

namespace BetterThanNothing
{
	class Device;
	class ShaderPool;
	class Shader;
	class ModelPool;
	class Model;
	class TexturePool;
	class Texture;

	class ResourceManager
	{
	private:
		Device* m_Device;

		ShaderPool* m_ShaderPool;
		ModelPool* m_ModelPool;
		TexturePool* m_TexturePool;

	public:
		ResourceManager(Device* device, const std::string& assetsPath);
		~ResourceManager();

		Shader* GetShader(const std::string& path);
		Model* GetModel(const std::string& path);
		Texture* GetTexture(const std::string& path);

		ShaderPool * GetShaderPool() const;
		ModelPool * GetModelPool() const;
		TexturePool * GetTexturePool() const;
	};
}
