#pragma once
#include "Utility/Log.h"

#define MN_ASSERT(x, ...) if (!(x)) { MN_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }