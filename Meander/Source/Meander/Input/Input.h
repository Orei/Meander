#pragma once
#include "Meander/Common.h"
#include "Key.h"
#include "InputAction.h"

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

		// TODO: Make this private or protected, we require a good way to access it though
		static void SetKeyState(Key key, InputAction action);

	private:
		static InputState m_KeyStates[(unsigned int)Key::MAX];
		static unsigned int m_CurrentFrame;
		
		static void Update();
		
		// Only allow application to update input.
		friend class Application;
	};
}