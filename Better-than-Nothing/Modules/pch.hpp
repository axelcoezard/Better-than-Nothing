#pragma once

#include <bits/stdc++.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>
#include <imgui_internal.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/hash.hpp>

#include <INIReader.h>

#include <entt/entt.hpp>

#include <glslang_c_interface.h>
#include <glslang_c_shader_types.h>
#include <resource_limits_c.h>

#include <spirv_cross.hpp>

#define MAX_FRAMES_IN_FLIGHT 30

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BIND_EVENT_LISTENER(fn) [this](auto&&... args) -> decltype(auto) {\
									return this->fn(std::forward<decltype(args)>(args)...);\
								}


typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;
typedef unsigned long	u64;

typedef signed char		i8;
typedef signed short	i16;
typedef signed int		i32;
typedef signed long		i64;

typedef float			f32;
typedef double			f64;

#define LOG_INFO(x)		std::cout << "\033[1;34m[INFO] " << x << "\033[0m" << std::endl;
#define LOG_SUCCESS(x)	std::cout << "\033[1;32m[SUCCESS] " << x << "\033[0m" << std::endl;
#define LOG_WARNING(x)	std::cout << "\033[1;33m[WARNING] " << x << "\033[0m" << std::endl;
#define LOG_ERROR(x)	std::cout << "\033[1;31m[ERROR] " << x << "\033[0m" << std::endl;
