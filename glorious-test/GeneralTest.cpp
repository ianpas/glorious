#include "stdafx.h"
#include "GeneralTest.h"

namespace pasha
{

	GeneralTest::GeneralTest(HINSTANCE current_instance, int show_mode, LPCWSTR title, int width, int height)
		:Glorious::Application(current_instance, show_mode, title, width, height)
	{
		Create();
	}

	int GeneralTest::Main()
	{
		auto run = [&]()
		{
			// check it because when handle input, we need this window is active
			// or the input will still be handled and incur unexpected result
			if (GetHandle() == GetActiveWindow())
			{
				m_Scene->Render();
			}

			wchar_t szTitle[128];
			swprintf_s(szTitle, L"Glorious (%0.2ffps)", 1 / Glorious::Time::m_DeltaTime);
			SetWindowTextW(GetHandle(), szTitle);
		};

		Run(run);

		return 0;
	}

	void GeneralTest::Create()
	{
		
		Glorious::DirectManager::GetSingleton(GetHandle());
		Glorious::GraphicsManager::GetSingleton();
		Glorious::FbxManager::GetSingleton();
		Glorious::BulletManager::GetSingleton();

		//
		m_Scene = std::make_unique<pasha::GeneralScene>();
	}
}
