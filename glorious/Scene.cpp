#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"


namespace Glorious
{
	Scene::Scene()
	{
		auto const& graphics_manager{ GraphicsManager::GetSingleton() };
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		std::memset(&m_ViewPort, 0, sizeof(m_ViewPort));
		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
		m_ViewPort.Width = graphics_manager.GetRenderTargetWidth();
		m_ViewPort.Height = graphics_manager.GetRenderTargetHeight();
		m_ViewPort.MinDepth = 0.f;
		m_ViewPort.MaxDepth = 1.f;
		device_context->RSSetViewports(1, &m_ViewPort);
	}

	void Scene::Render()
	{
		auto render = [&]()
		{
			Glorious::Input::UpdateCurrent();

			auto const& graphics_manager{ GraphicsManager::GetSingleton() };
			//graphics_manager.Render([&] { Time::Measure(std::bind(&Scene::OnRender, *this)); });
			graphics_manager.Render([&] {OnRender(); });

			Glorious::Input::UpdatePrevious();
		};

		Time::Measure(render);
		Debug::Log("DeltaTime: " + std::to_string(Time::m_DeltaTime));
		Debug::Log("TotalTime: " + std::to_string(Time::m_TotalTime));
	}

	void Scene::OnRender()
	{
		Glorious::BulletManager::GetSingleton().GetPhysicsWorld()->stepSimulation(Time::m_DeltaTime);

		for (auto& each : m_GameObjects)
		{
			each->Update();
			each->Render();
		}
	}
}