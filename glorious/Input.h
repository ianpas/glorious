#pragma once

namespace Glorious
{
	template <typename T>
	constexpr auto to_underlying(T enum_value) noexcept
	{
		return static_cast<std::underlying_type_t<T>>(enum_value);
	}

	enum class KeyCode
	{
		W = 0x57, // Win32 Virtual-Key Codes
		A = 0x41,
		S = 0x53,
		D = 0x44,
		Mouse0 = VK_LBUTTON, // The left mouse button
		Mouse1 = VK_RBUTTON
	};

	class Input
	{
	public:
		// return true if the button is pressed
		static bool GetKey(KeyCode key);

		// return true only in the frame you press the button
		static bool GetKeyDown(KeyCode key);

		// return true only in the frame you release the button
		static bool GetKeyUp(KeyCode key);

		static void UpdateCurrent();
		static void UpdatePrevious();

	private:
		static std::unordered_map<KeyCode, bool> m_PreviousKeyStates;
		static std::unordered_map<KeyCode, bool> m_CurrentKeyStates;
		static std::vector<KeyCode>				 m_KeyCodes;
		
	};
}