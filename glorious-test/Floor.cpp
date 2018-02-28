#include "stdafx.h"
#include "Floor.h"
#include "FloorController.h"

namespace pasha
{
	Floor::Floor(Glorious::IScene* scene)
		:Glorious::GameObject(scene)
	{
		Awake();
	}

	void Floor::Awake()
	{
		
		AddComponent<Glorious::Transform>(this);

		float width = 10.f;
		float length = 200.f;
		float height = 0.5f;
		auto transform = GetComponent<Glorious::ITransform>();
		transform->SetPosition(DirectX::XMFLOAT3{ 0.f,-height / 2,length / 2 - 3.f });
		transform->SetScale(DirectX::XMFLOAT3{ width,height,length });

		AddComponent<Glorious::Mesh>(this, R"(asset\floor.tga)", R"(asset\floor.fbx)");
		AddComponent<Glorious::Renderer>(this);
		AddComponent<Glorious::VertexShader>(R"(asset\PashaShader.pashavs)", this);
		AddComponent<Glorious::PixelShader>(R"(asset\PashaShader.pashaps)", this);

		AddComponent<Glorious::Rigidbody>(this, 0, new btBoxShape{ btVector3{ width / 2,height / 2,length / 2 } });
		AddComponent<FloorController>(this);
	}
}