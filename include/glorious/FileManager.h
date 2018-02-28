#pragma once

namespace Glorious
{
	class FileManager
	{
	public:
		static std::vector<char> ReadBinaryFile(std::string const& file_path);
		static std::string GetExePath();
	};
}


