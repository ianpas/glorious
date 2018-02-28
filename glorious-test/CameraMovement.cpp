#include "stdafx.h"
#include "CameraMovement.h"

namespace pasha
{
	CameraMovement::CameraMovement(Glorious::IGameObject * game_object)
		:Component(game_object)
	{

	}

	void CameraMovement::Start()
	{
		m_Transform = GetComponent<Glorious::ITransform>();
		m_Camera = GetComponent<Glorious::ICamera>();
	}

	void CameraMovement::Update()
	{
		using namespace Glorious;

		auto view = m_Camera->GetViewMatrix();
		auto inverse_view = DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(view), view);

		auto forward = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f);
		forward = DirectX::XMVector4Transform(forward, inverse_view);

		auto right = DirectX::XMVectorSet(1.f, 0.f, 0.f, 0.f);
		right = DirectX::XMVector4Transform(right, inverse_view);

		DirectX::XMFLOAT3 movement{ 0.f,0.f,0.f };

		if (Input::GetKey(KeyCode::W))
		{
			DirectX::XMStoreFloat3(&movement, forward);
		}
		else if (Input::GetKey(KeyCode::S))
		{
			DirectX::XMStoreFloat3(&movement, DirectX::XMVectorNegate(forward));
		}
		/*else if (Input::GetKey(KeyCode::D))
		{
			DirectX::XMStoreFloat3(&movement, right);
		}
		else if (Input::GetKey(KeyCode::A))
		{
			DirectX::XMStoreFloat3(&movement, DirectX::XMVectorNegate(right));
		}*/

		auto eye = m_Camera->GetEye();
		eye.x += 0.1*movement.x;
		eye.y += 0.1*movement.y;
		eye.z += 0.1*movement.z;
		m_Camera->SetEye(eye);
	}


}