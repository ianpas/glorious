#include "stdafx.h"
#include "Player.h"
#include "PlayerMovement.h"

namespace pasha
{
	Player::Player(Glorious::IScene* scene)
		:Glorious::GameObject(scene)
	{
		Awake();
	}

	void Player::Awake()
	{

		AddComponent<Glorious::Transform>(this);
		auto transform = GetComponent<Glorious::ITransform>();

		transform->SetPosition(DirectX::XMFLOAT3{ 0.f,0.5f,0.f });
		transform->SetRotation(DirectX::XMFLOAT3{ 0.f,0.f,0.f });

		AddComponent<Glorious::Mesh>(this, R"(asset\minecraft.tga)", R"(asset\player.fbx)");
		AddComponent<Glorious::Renderer>(this);
		AddComponent<Glorious::VertexShader>(R"(asset\PashaShader.pashavs)", this);
		AddComponent<Glorious::PixelShader>(R"(asset\PashaShader.pashaps)", this);

		AddComponent<Glorious::Rigidbody>(this, 1, new btBoxShape{ btVector3{0.5,0.5,0.5} });
		AddComponent<PlayerMovement>(this);


	}
}