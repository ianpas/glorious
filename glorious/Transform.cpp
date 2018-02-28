#include "stdafx.h"
#include "Transform.h"

namespace Glorious
{
	Transform::Transform(IGameObject* game_object)
		:Component(game_object)
	{
		m_Position = DirectX::XMFLOAT3{ 0.f,0.f,0.f };
		m_Rotation = DirectX::XMFLOAT3{ 0.f,0.f,0.f };
		m_Scale = DirectX::XMFLOAT3{ 1.f,1.f,1.f };
	}

	inline DirectX::XMMATRIX XM_CALLCONV Transform::GetWorldMatrix() const
	{
		DirectX::XMMATRIX scale =
		{
			m_Scale.x	,0			,0			,0,
			0			,m_Scale.y	,0			,0,
			0			,0			,m_Scale.z	,0,
			0			,0			,0			,1
		};

		auto to_radian = [&](float degree)
		{
			return (degree*DirectX::XM_PI) / 180.f;
		};

		float angle = to_radian(m_Rotation.x);

		DirectX::XMMATRIX x_rotation =
		{
			1	,0					,0					,0,
			0	,std::cos(angle)	,std::sin(angle)	,0,
			0	,-std::sin(angle)	,std::cos(angle)	,0,
			0	,0					,0					,1
		};

		angle = to_radian(m_Rotation.y);

		DirectX::XMMATRIX y_rotation =
		{
			std::cos(angle)	,0	,-std::sin(angle)	,0,
			0				,1	,0					,0,
			std::sin(angle)	,0	,std::cos(angle)	,0,
			0				,0	,0					,1
		};

		angle = to_radian(m_Rotation.z);

		DirectX::XMMATRIX z_rotation =
		{
			std::cos(angle)	,std::sin(angle)	,0	,0,
		   -std::sin(angle)	,std::cos(angle)	,0	,0,
			0				,0					,1	,0,
			0				,0					,0	,1
		};

		DirectX::XMMATRIX rotation = x_rotation * y_rotation*z_rotation;

		DirectX::XMMATRIX translation =
		{
			1				,0				,0				,0,
			0				,1				,0				,0,
			0				,0				,1				,0,
			m_Position.x	,m_Position.y	,m_Position.z	,1
		};

		return scale * rotation * translation;
	}

	void Transform::Translate(DirectX::XMFLOAT3 translation)
	{
		m_Position.x += translation.x;
		m_Position.y += translation.y;
		m_Position.z += translation.z;
	}

	DirectX::XMFLOAT3 Transform::GetPosition() const
	{
		return m_Position;
	}

	DirectX::XMFLOAT3 Transform::GetRotation() const
	{
		return m_Rotation;
	}

	DirectX::XMFLOAT3 Transform::GetScale() const
	{
		return m_Scale;
	}

	void Transform::SetPosition(DirectX::XMFLOAT3 const & position)
	{
		m_Position = position;
	}

	void Transform::SetRotation(DirectX::XMFLOAT3 const & rotation)
	{
		m_Rotation = rotation;
	}

	void Transform::SetScale(DirectX::XMFLOAT3 const & scale)
	{
		m_Scale = scale;
	}

}