#pragma once
#include "Meander/Common.h"
#include "Key.h"
#include "MouseButton.h"
#include "InputAction.h"
#include <glm/vec2.hpp>

namespace Meander
{
	struct InputState
	{
		InputAction Action = InputAction::Release;
		uint32_t Frame = 0;

		InputState(){}
		InputState(InputAction action, uint32_t frame)
			: Action(action), Frame(frame)
		{
		}
	};

	class Input
	{
	public:
		Input();
		virtual ~Input();

		/* Whether the key is currently down. */
		bool IsKeyDown(Key key);
	
		/* Whether the key is currently up. */
		bool IsKeyUp(Key key);
	
		/* Whether the key was pressed this frame. */
		bool IsKeyPressed(Key key);
	
		/* Whether the key was released this frame. */
		bool IsKeyReleased(Key key);
	
		/* Returns a normalized float depending on the pressed keys. */
		float GetKeysAxis(Key negative, Key positive);
	
		/* Whether the mouse button is currently pressed. */
		bool IsMouseDown(MouseButton button);
	
		/* Whether the mouse button is currently released. */
		bool IsMouseUp(MouseButton button);
	
		/* Whether the mouse button was pressed this frame. */
		bool IsMousePressed(MouseButton button);
	
		/* Whether the mouse button was released this frame. */
		bool IsMouseReleased(MouseButton button);
	
		/* Returns the mouse position. */
		const glm::vec2& GetMousePosition() { return m_MousePosition; }
		const glm::vec2 GetMouseDelta() { return m_MousePosition - m_PreviousMousePosition; }

		/* Returns the input instance. */
		inline static Input* Get() { return s_Instance; }

	protected:
		void SetKeyState(Key key, InputAction action);
		void SetMouseButtonState(MouseButton button, InputAction action);
		void SetMousePosition(const glm::vec2& position);

	private:
		InputState m_KeyStates[Key::MAX];
		InputState m_MouseStates[MouseButton::MAX];
		glm::vec2 m_MousePosition = {};
		glm::vec2 m_PreviousMousePosition = {};
		uint32_t m_CurrentFrame = 0;
		
		void Update() { ++m_CurrentFrame; m_PreviousMousePosition = m_MousePosition; }

		static Input* s_Instance;
		
		// Only allow application to update input.
		friend class Application;
	};
}