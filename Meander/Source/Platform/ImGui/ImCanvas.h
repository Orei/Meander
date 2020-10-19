#pragma once
#include "Meander/UI/Canvas.h"

namespace Meander
{
    class ImCanvas : public Canvas
    {
    public:
        /* Initializes the canvas. */
        virtual void Initialize(Window* window, RenderContext* renderer);

        /* Begins a new UI render frame. */
        virtual void Begin();

        /* Ends the active UI render frame and renders. */
        virtual void End();
    };
}
