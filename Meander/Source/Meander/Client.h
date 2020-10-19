#pragma once
#include "GameTime.h"

namespace Meander
{
    class Application;
    class RenderContext;
    class Window;
    class Canvas;
    class Input;
    
    class Client
    {
    public:
        Client() { }
        virtual ~Client() { }

    protected:
        virtual void Initialize() = 0;
        virtual void Load() = 0;
        virtual void Update(GameTime& gameTime) = 0;
        virtual void Render(GameTime& gameTime) = 0;
        virtual void RenderUI(GameTime& gameTime) = 0;
        
        Application* m_Application = nullptr;
        RenderContext* m_RenderContext = nullptr;
        Window* m_Window = nullptr;
        Canvas* m_Canvas = nullptr;
        Input* m_Input = nullptr;

    private:
        void Initialize_Internal(Application* app, RenderContext* graphics, Window* window, Canvas* canvas, Input* input)
        {
            m_Application = app;
            m_RenderContext = graphics;
            m_Window = window;
            m_Canvas = canvas;
            m_Input = input;
        }
       
        friend class Application;
    };
}
