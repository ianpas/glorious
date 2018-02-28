#pragma once

namespace Glorious
{
	class IApplication
	{
	public:
		virtual ~IApplication() = default;

	public:
		virtual void Run(std::function<void()> run)const = 0;
		virtual HWND GetHandle()const = 0;
	};
}