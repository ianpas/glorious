#pragma once
#include "..\include\win32\include.h"
#include "GeneralScene.h"

namespace pasha
{
	class GeneralTest : public Glorious::Application
	{
	private:
		std::unique_ptr<Glorious::IScene> m_Scene;

	public:
		GeneralTest(HINSTANCE current_instance, int show_mode, LPCWSTR title, int width, int height);
		
		int Main();

	private:
		void Create();
	};

}



