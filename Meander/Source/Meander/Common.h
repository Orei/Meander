#pragma once
#include "Utility/Log.h"

#define MN_ASSERT(x, ...) if (!(x)) { MN_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }

#define WORLD_RIGHT glm::vec3(1.f, 0.f, 0.f)
#define WORLD_UP glm::vec3(0.f, 1.f, 0.f)
#define WORLD_FORWARD glm::vec3(0.f, 0.f, -1.f)

#define DIFFUSE_SLOT 0
#define NORMAL_SLOT 1
#define SPECULAR_SLOT 2
#define EMISSIVE_SLOT 3
#define SHADOWMAP_SLOT 4
#define SKYBOX_SLOT 5
#define COLOR_BUFFER_SLOT 6
#define DEPTH_BUFFER_SLOT 7

namespace Meander
{
	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}