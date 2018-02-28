#include "stdafx.h"
#include "GeneralScene.h"
#include "Player.h"
#include "Crate.h"
#include "Floor.h"
#include "MainCamera.h"
#include "DirectionalLight.h"
#include "CameraFollow.h"

namespace pasha
{
	GeneralScene::GeneralScene()
		:Glorious::Scene()
	{
		AddGameObject<MainCamera>(this);
		auto camera = m_GameObjects.back();

		AddGameObject<DirectionalLight>(this);


		AddGameObject<Player>(this);
		auto player = m_GameObjects.back();

		AddGameObject<Floor>(this);

		std::vector<DirectX::XMFLOAT3> positions
		{
			DirectX::XMFLOAT3{ 0.f,0.5f,10.f },
			DirectX::XMFLOAT3{ 0.f,0.5f,20.f },
			DirectX::XMFLOAT3{ 3.f,0.5f,20.f },
			DirectX::XMFLOAT3{-3.f,0.5f,20.f },
			DirectX::XMFLOAT3{-1.f,0.5f,30.f },
			DirectX::XMFLOAT3{ 0.f,0.5f,30.f },
			DirectX::XMFLOAT3{ 2.f,0.5f,30.f },
			DirectX::XMFLOAT3{ 2.f,0.5f,40.f },
			DirectX::XMFLOAT3{ 1.f,0.5f,50.f }
		};

		for (auto each : positions)
		{
			AddGameObject<Crate>(this);
			auto transform = m_GameObjects.back()->GetComponent<Glorious::ITransform>();
			transform->SetPosition(each);
		}

		//
		camera->GetComponent<CameraFollow>()->m_Target = player->GetComponent<Glorious::ITransform>();
	}
}