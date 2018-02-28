#include "stdafx.h"
#include "PlayerMovement.h"

namespace pasha
{
	PlayerMovement::PlayerMovement(Glorious::IGameObject * game_object)
		:Component(game_object)
	{

	}

	void PlayerMovement::Start()
	{
		m_Transform = GetComponent<Glorious::ITransform>();
		m_Rigidbody = GetComponent<Glorious::IRigidbody>();

		m_Rigidbody->SetCollisionHandler(this);
	}

	void PlayerMovement::OnCollisionEnter()
	{
		//Debug::PopMessageBox("cube collision enter");
	}

	void PlayerMovement::Update()
	{

		if (m_Transform->GetPosition().z > 40.f)
		{
			return;
		}

		float force = 600.f;

		if (Glorious::Input::GetKey(Glorious::KeyCode::A))
		{
			m_Rigidbody->AddForce(DirectX::XMFLOAT3{ -force * Glorious::Time::m_DeltaTime,0.f,0.f });
		}
		else if (Glorious::Input::GetKey(Glorious::KeyCode::D))
		{
			m_Rigidbody->AddForce(DirectX::XMFLOAT3{ force * Glorious::Time::m_DeltaTime,0.f,0.f });
		}
		/*else if (Input::GetKey(KeyCode::W))
		{
			m_Rigidbody->AddForce(DirectX::XMFLOAT3{ 0.f,0.f,force * Time::m_DeltaTime });
		}
		else if (Input::GetKey(KeyCode::S))
		{
			m_Rigidbody->AddForce(DirectX::XMFLOAT3{ 0.f,0.f,-force * Time::m_DeltaTime });
		}*/

		m_Rigidbody->AddForce(DirectX::XMFLOAT3{ 0.f,0.f,force * Glorious::Time::m_DeltaTime });


	}


}