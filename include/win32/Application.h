#pragma once
#include "IApplication.h"
#include "IWindow.h"

namespace Glorious
{
	class Application :public IApplication
	{
	private:
		std::unique_ptr<IWindow> m_Window;

	public:
		Application(HINSTANCE current_instance, int show_mode, LPCWSTR title, int width, int height);

	public:
		void Run(std::function<void()> run) const override;
		HWND GetHandle() const override;
	};

}
