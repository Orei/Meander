#include "pch.h"
#include "Canvas.h"

namespace Meander
{
    Canvas* Canvas::s_Instance = nullptr;

    Canvas::Canvas()
    {
        MN_ASSERT(s_Instance == nullptr, "An instance of Canvas already exists.");
        s_Instance = this;
    }

    Canvas::~Canvas()
    {
        s_Instance = nullptr;
    }
}
