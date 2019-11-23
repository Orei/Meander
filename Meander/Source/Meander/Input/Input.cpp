#include "pch.h"
#include "Input.h"

namespace Meander
{
	InputState Input::m_KeyStates[(unsigned int)Key::MAX];
	InputState Input::m_MouseStates[(unsigned int)MouseButton::MAX];
	glm::vec2 Input::m_MousePosition = glm::vec2(0.f);
	unsigned int Input::m_CurrentFrame = 0;

	bool Input::IsKeyDown(Key key)
	{
		const InputState& state = m_KeyStates[(unsigned int)key];
		return state.Action == InputAction::Press || state.Action == InputAction::Repeat;
	}

	bool Input::IsKeyUp(Key key)
	{
		return !IsKeyDown(key);
	}

	bool Input::IsKeyPressed(Key key)
	{
		const InputState& state = m_KeyStates[(unsigned int)key];
		return state.Action == InputAction::Press && state.Frame == m_CurrentFrame;
	}

	bool Input::IsKeyReleased(Key key)
	{
		const InputState& state = m_KeyStates[(unsigned int)key];
		return state.Action == InputAction::Release && state.Frame == m_CurrentFrame;
	}

	bool Input::IsMouseDown(MouseButton button)
	{
		const InputState& state = m_KeyStates[(unsigned int)button];
		return state.Action == InputAction::Press;
	}

	bool Input::IsMouseUp(MouseButton button)
	{
		return !IsMouseDown(button);
	}

	bool Input::IsMousePressed(MouseButton button)
	{
		const InputState& state = m_MouseStates[(unsigned int)button];
		return state.Action == InputAction::Press && state.Frame == m_CurrentFrame;
	}

	bool Input::IsMouseReleased(MouseButton button)
	{
		const InputState& state = m_MouseStates[(unsigned int)button];
		return state.Action == InputAction::Release && state.Frame == m_CurrentFrame;
	}

	void Input::SetKeyState(Key key, InputAction action)
	{
		InputState& state = m_KeyStates[(unsigned int)key];
		state.Action = action;
		state.Frame = m_CurrentFrame;
	}

	void Input::SetMouseButtonState(MouseButton button, InputAction action)
	{
		InputState& state = m_MouseStates[(unsigned int)button];
		state.Action = action;
		state.Frame = m_CurrentFrame;
	}

	void Input::SetMousePosition(const glm::vec2& position)
	{
		m_MousePosition.x = position.x;
		m_MousePosition.y = position.y;
	}
}