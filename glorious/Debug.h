#pragma once

namespace Glorious
{
	class Debug
	{
	public:
		static void Log(std::string const& message);
		static void PopMessageBox(std::string const& message);
	};
}
