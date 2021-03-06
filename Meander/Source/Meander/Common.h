#pragma once
#include "Utility/Log.h"

#ifdef MN_DEBUG
#define MN_ASSERT(x, ...) if (!(x)) { MN_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
#define MN_ASSERT(x, ...)
#endif

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