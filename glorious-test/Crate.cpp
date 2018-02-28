#include "stdafx.h"
#include "Crate.h"

namespace pasha
{
	Crate::Crate(Glorious::IScene* scene)
		:Glorious::GameObject(scene)
	{
		Awake();
	}

	void Crate::Awake()
	{


		AddComponent<Glorious::Transform>(this);

		AddComponent<Glorious::Mesh>(this, R"(asset\minecraft.tga)", R"(asset\enemy.fbx)");

		AddComponent<Glorious::Renderer>(this);
		AddComponent<Glorious::VertexShader>(R"(asset\PashaShader.pashavs)", this);
		AddComponent<Glorious::PixelShader>(R"(asset\PashaShader.pashaps)", this);

		AddComponent<Glorious::Rigidbody>(this, 1, new btBoxShape{ btVector3{0.5,0.5,0.5} });


	}
}