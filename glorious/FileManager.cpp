#include "stdafx.h"
#include "FileManager.h"

namespace Glorious
{
	std::vector<char> FileManager::ReadBinaryFile(std::string const & file_path)
	{
		auto pFile = file_path.c_str();

		HANDLE hFile = CreateFileA(pFile, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		FILE_STANDARD_INFO FileInformation;
		GetFileInformationByHandleEx(hFile, FileStandardInfo, &FileInformation, sizeof(FileInformation));

		std::vector<char> vData((size_t)FileInformation.EndOfFile.LowPart);

		DWORD nRead;
		ReadFile(hFile, vData.data(), FileInformation.EndOfFile.LowPart, &nRead, nullptr);

		CloseHandle(hFile);

		return std::move(vData);
	}

	std::string FileManager::GetExePath()
	{
		char buffer[MAX_PATH];
		GetModuleFileNameA(nullptr, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string path = std::string(buffer).substr(0, pos);
		return path;
	}
}
