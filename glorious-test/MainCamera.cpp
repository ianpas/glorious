#include "stdafx.h"
#include "MainCamera.h"
#include "CameraFollow.h"

namespace pasha
{
	MainCamera::MainCamera(Glorious::IScene* scene)
		:Glorious::GameObject(scene)
	{
		Awake();
	}

	void MainCamera::Awake()
	{

		AddComponent<Glorious::Transform>(this);

		// TODO: add camera follow first, the order matters , but why?...
		AddComponent<CameraFollow>(this);

		AddComponent<Glorious::Camera>(this);
		auto camera = GetComponent<Glorious::ICamera>();
		camera->SetEye(DirectX::XMFLOAT3{ 0.f,5.f,-10.f });
		camera->SetFocus(DirectX::XMFLOAT3{ 0.f,2.f,0.f });

	}


}