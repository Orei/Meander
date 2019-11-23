#include "pch.h"
#include "Input.h"

namespace Meander
{
	InputState Input::m_KeyStates[(unsigned int)Key::MAX];
	unsigned int Input::m_CurrentFrame = 0;

	void Input::Update()
	{
		m_CurrentFrame++;
	}

	bool Input::IsKeyDown(Key key)
	{
		const InputState& state = m_KeyStates[(unsigned int)key];
		return state.Action == InputAction::Press || state.Action == InputAction::Repeat;
	}

	bool Input::IsKeyUp(Key key)
	{
		const InputState& state = m_KeyStates[(unsigned int)key];
		return state.Action == InputAction::Release;
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

	void Input::SetKeyState(Key key, InputAction action)
	{
		InputState& state = m_KeyStates[(unsigned int)key];
		state.Action = action;
		state.Frame = m_CurrentFrame;
	}
}