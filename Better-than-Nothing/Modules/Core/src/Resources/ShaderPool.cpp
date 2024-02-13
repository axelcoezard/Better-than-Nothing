#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	ShaderPool::ShaderPool(const std::string& basePath, Device* device): ResourcePool(basePath)
	{
		m_Device = device;
	}

	ShaderPool::~ShaderPool()
	{
		for (auto& [path, shader] : m_Resources)
		{
			vkDestroyShaderModule(m_Device->GetVkDevice(), shader->module, nullptr);
			delete shader;
		}
	}

	Shader* ShaderPool::GetResource(const std::string& filePath)
	{
		auto it = m_Resources.find(filePath);
		if (it != m_Resources.end())
		{
			return it->second;
		}

		std::vector<char> shaderCode = ReadFile(m_BasePath + filePath);
		glslang_stage_t shaderStage = GetShaderStage(filePath);
		glslang_program_t* shaderProgram = GetShaderProgram(shaderCode, shaderStage);
		ShaderDetails shaderDetails = GetShaderDetails(shaderProgram);
		VkShaderModule shaderModule = CreateShaderModule(shaderProgram);

		Shader* shader = new Shader();
		shader->filePath = filePath;
		shader->stage = shaderStage;
		shader->module = shaderModule;
		shader->details = shaderDetails;

		LOG_SUCCESS("ShaderPool: " + filePath);
		std::cout << "=> Uniform Buffers: " << shaderDetails.uniformBufferCount << std::endl;
		std::cout << "=> Storage Buffers: " << shaderDetails.storageBufferCount << std::endl;
		std::cout << "=> Samplers: " << shaderDetails.samplerCount << std::endl;

		m_Resources[filePath] = shader;
		return shader;
	}

	std::vector<char> ShaderPool::ReadFile(const std::string& filePath)
	{
		std::ifstream file(filePath, std::ios::ate); //  | std::ios::binary for spv files

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t) file.tellg();
		std::vector<char> buffer;

		buffer.resize(fileSize);
		std::memset(buffer.data(), 0, fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize - 1);
		file.close();

		return buffer;
	}

	glslang_program_t* ShaderPool::GetShaderProgram(std::vector<char> shaderCode, glslang_stage_t stage)
	{
		const glslang_input_t input = {
			.language = GLSLANG_SOURCE_GLSL,
			.stage = stage,
			.client = GLSLANG_CLIENT_VULKAN,
			.client_version = GLSLANG_TARGET_VULKAN_1_3,
			.target_language = GLSLANG_TARGET_SPV,
			.target_language_version = GLSLANG_TARGET_SPV_1_0,
			.code = shaderCode.data(),
			.default_version = 450,
			.default_profile = GLSLANG_NO_PROFILE,
			.force_default_version_and_profile = false,
			.forward_compatible = false,
			.messages = GLSLANG_MSG_DEFAULT_BIT,
			.resource = glslang_default_resource(),
			.callbacks = {},
			.callbacks_ctx = nullptr
		};

		glslang_initialize_process();

		glslang_shader_t* shader = glslang_shader_create(&input);

		if (!glslang_shader_preprocess(shader, &input))
			throw std::runtime_error("failed to preprocess shader: " + std::string(glslang_shader_get_info_log(shader)));

		if (!glslang_shader_parse(shader, &input))
			throw std::runtime_error("failed to parse shader: " + std::string(glslang_shader_get_info_log(shader)));

		glslang_program_t* program = glslang_program_create();
		glslang_program_add_shader(program, shader);

		if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT))
			throw std::runtime_error("failed to compile shader program: " + std::string(glslang_program_get_info_log(program)));

		glslang_program_SPIRV_generate(program, input.stage);

		if (glslang_program_SPIRV_get_messages(program))
			printf("%s", glslang_program_SPIRV_get_messages(program));

		glslang_shader_delete( shader );

		return program;
	}

	VkShaderModule ShaderPool::CreateShaderModule(glslang_program_t* program) {

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = glslang_program_SPIRV_get_size(program) * sizeof(unsigned int);
		createInfo.pCode = glslang_program_SPIRV_get_ptr(program);

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(m_Device->GetVkDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}

		glslang_program_delete(program);

		return shaderModule;
	}

	glslang_stage_t ShaderPool::GetShaderStage(const std::string& filePath)
	{
		if (filePath.find(".vert") != std::string::npos)
			return GLSLANG_STAGE_VERTEX;
		else if (filePath.find(".frag") != std::string::npos)
			return GLSLANG_STAGE_FRAGMENT;
		else if (filePath.find(".comp") != std::string::npos)
			return GLSLANG_STAGE_COMPUTE;
		else if (filePath.find(".geom") != std::string::npos)
			return GLSLANG_STAGE_GEOMETRY;

		throw std::runtime_error("unknown shader stage");
	}

	ShaderDetails ShaderPool::GetShaderDetails(glslang_program_t* program)
	{
		const uint32_t* spirvCode = glslang_program_SPIRV_get_ptr(program);
		const size_t spirvSize = glslang_program_SPIRV_get_size(program);

		spirv_cross::Compiler compiler(spirvCode, spirvSize);
		spirv_cross::ShaderResources shaderResources = compiler.get_shader_resources();

		ShaderDetails details;
		details.uniformBufferCount = shaderResources.uniform_buffers.size();
		details.storageBufferCount = shaderResources.storage_buffers.size();
		details.samplerCount = shaderResources.sampled_images.size();

		return details;
	}
};
