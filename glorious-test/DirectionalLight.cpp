#include "stdafx.h"
#include "DirectionalLight.h"

namespace pasha
{

	DirectionalLight::DirectionalLight(Glorious::IScene * scene)
		:Glorious::GameObject(scene)
	{
		Awake();
	}

	void DirectionalLight::Awake()
	{
		AddComponent<Glorious::Transform>(this);
		AddComponent<Glorious::Light>(this);

		GetComponent<Glorious::ITransform>()->SetPosition(DirectX::XMFLOAT3{ 0.f,5,0.f });

	}
}
