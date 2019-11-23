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
		unsigned int Frame = -1;

		InputState(){}
		InputState(InputAction action, unsigned int frame)
			: Action(action), Frame(frame)
		{
		}
	};

	class Input
	{
	public:
		/* Whether the key is currently pressed. */
		static bool IsKeyDown(Key key);

		/* Whether the key is currently released. */
		static bool IsKeyUp(Key key);

		/* Whether the key was pressed this frame. */
		static bool IsKeyPressed(Key key);

		/* Whether the key was released this frame. */
		static bool IsKeyReleased(Key key);

		/* Whether the mouse button is currently pressed. */
		static bool IsMouseDown(MouseButton button);

		/* Whether the mouse button is currently released. */
		static bool IsMouseUp(MouseButton button);

		/* Whether the mouse button was pressed this frame. */
		static bool IsMousePressed(MouseButton button);

		/* Whether the mouse button was released this frame. */
		static bool IsMouseReleased(MouseButton button);

		// TODO: Make these private or protected, we require a good way to access it though
		static void SetKeyState(Key key, InputAction action);
		static void SetMouseButtonState(MouseButton button, InputAction action);
		static void SetMousePosition(const glm::vec2& position);

		/* Returns the mouse position. */
		static const glm::vec2& GetMousePosition() { return m_MousePosition; }

	private:
		static InputState m_KeyStates[(unsigned int)Key::MAX];
		static InputState m_MouseStates[(unsigned int)MouseButton::MAX];
		static glm::vec2 m_MousePosition;
		static unsigned int m_CurrentFrame;
		
		static void Update() { m_CurrentFrame++; }
		
		// Only allow application to update input.
		friend class Application;
	};
}