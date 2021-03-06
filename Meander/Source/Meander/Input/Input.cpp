#include "pch.h"
#include "Input.h"

namespace Meander
{
	Input* Input::s_Instance = nullptr;

	Input::Input()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Input already exists.");
		s_Instance = this;
	}

	Input::~Input()
	{
		s_Instance = nullptr;
	}

	bool Input::IsKeyDown(Key key)
	{
		const InputState& state = m_KeyStates[(uint32_t)key];
		return state.Action == InputAction::Press || state.Action == InputAction::Repeat;
	}

	bool Input::IsKeyUp(Key key)
	{
		return !IsKeyDown(key);
	}

	bool Input::IsKeyPressed(Key key)
	{
		const InputState& state = m_KeyStates[(uint32_t)key];
		return state.Action == InputAction::Press && state.Frame == m_CurrentFrame;
	}

	bool Input::IsKeyReleased(Key key)
	{
		const InputState& state = m_KeyStates[(uint32_t)key];
		return state.Action == InputAction::Release && state.Frame == m_CurrentFrame;
	}

	float Input::GetKeysAxis(Key negative, Key positive)
	{
		return (float)(IsKeyDown(positive) - IsKeyDown(negative));
	}

	bool Input::IsMouseDown(MouseButton button)
	{
		const InputState& state = m_KeyStates[(uint32_t)button];
		return state.Action == InputAction::Press;
	}

	bool Input::IsMouseUp(MouseButton button)
	{
		return !IsMouseDown(button);
	}

	bool Input::IsMousePressed(MouseButton button)
	{
		const InputState& state = m_MouseStates[(uint32_t)button];
		return state.Action == InputAction::Press && state.Frame == m_CurrentFrame;
	}

	bool Input::IsMouseReleased(MouseButton button)
	{
		const InputState& state = m_MouseStates[(uint32_t)button];
		return state.Action == InputAction::Release && state.Frame == m_CurrentFrame;
	}

	void Input::SetKeyState(Key key, InputAction action)
	{
		InputState& state = m_KeyStates[(uint32_t)key];
		state.Action = action;
		state.Frame = m_CurrentFrame;
	}

	void Input::SetMouseButtonState(MouseButton button, InputAction action)
	{
		InputState& state = m_MouseStates[(uint32_t)button];
		state.Action = action;
		state.Frame = m_CurrentFrame;
	}

	void Input::SetMousePosition(const glm::vec2& position)
	{
		m_MousePosition.x = position.x;
		m_MousePosition.y = position.y;
	}
}