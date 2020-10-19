#pragma once

namespace Meander
{
	class Window;
	class RenderContext;

	class Canvas
	{
	public:
		Canvas();
		virtual ~Canvas();

		/* Initializes the canvas. */
		virtual void Initialize(Window* window, RenderContext* renderer) = 0;

		/* Begins a new UI render frame. */
		virtual void Begin() = 0;

		/* Ends the active UI render frame and renders. */
		virtual void End() = 0;

		/* Returns the canvas instance. */
		inline static Canvas* Get() { return s_Instance; }

	protected:
		Window* m_Window = nullptr;
		RenderContext* m_Renderer = nullptr;

		static Canvas* s_Instance;
	};
}