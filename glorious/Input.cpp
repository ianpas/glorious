#include "stdafx.h"
#include "Input.h"


namespace Glorious
{

	// true : previous state is pressed
	// false: previous state is not pressed
	std::vector<KeyCode> Input::m_KeyCodes
	{
		KeyCode::W,
		KeyCode::A,
		KeyCode::S,
		KeyCode::D,
		KeyCode::Mouse0,
		KeyCode::Mouse1
	};

	std::unordered_map<KeyCode, bool> Input::m_PreviousKeyStates =
	{
		{ KeyCode::W,false },
		{ KeyCode::A,false },
		{ KeyCode::S,false },
		{ KeyCode::D,false },
		{ KeyCode::Mouse0,false },
		{ KeyCode::Mouse1,false }
	};

	std::unordered_map<KeyCode, bool> Input::m_CurrentKeyStates =
	{
		{ KeyCode::W,false },
		{ KeyCode::A,false },
		{ KeyCode::S,false },
		{ KeyCode::D,false },
		{ KeyCode::Mouse0,false },
		{ KeyCode::Mouse1,false }
	};

	bool Input::GetKeyDown(KeyCode key)
	{
		return m_CurrentKeyStates[key] && !m_PreviousKeyStates[key];
	}

	bool Input::GetKeyUp(KeyCode key)
	{
		return !m_CurrentKeyStates[key] && m_PreviousKeyStates[key];
	}

	void Input::UpdateCurrent()
	{
		for (auto const& each : m_KeyCodes)
		{
			m_CurrentKeyStates[each] = GetAsyncKeyState(to_underlying(each)) & 0x8000;
		}

	}

	void Input::UpdatePrevious()
	{
		for (auto const& each : m_KeyCodes)
		{
			m_PreviousKeyStates[each] = m_CurrentKeyStates[each];
		}

	}

	bool Input::GetKey(KeyCode key)
	{
		return m_CurrentKeyStates[key];
	}
}
