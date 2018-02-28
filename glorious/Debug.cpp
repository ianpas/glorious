#include "stdafx.h"
#include "Debug.h"

namespace Glorious
{
	void Debug::Log(std::string const & message)
	{
		OutputDebugStringA(message.c_str());
		OutputDebugStringA("\n");
	}

	void Debug::PopMessageBox(std::string const & message)
	{
		MessageBoxA(nullptr, message.c_str(), "Message", MB_OK);
	}
}