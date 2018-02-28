#pragma once

namespace Glorious
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;

	public:
		virtual HWND GetHandle()const = 0;
	};
}