#pragma once
#include "ITransform.h"
#include "Component.h"

namespace Glorious
{
	class Transform :public ITransform, public Component
	{
	private:
		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT3 m_Rotation; // in degree
		DirectX::XMFLOAT3 m_Scale;

	public:
		Transform(IGameObject* game_object);

	public:
		inline DirectX::XMMATRIX XM_CALLCONV GetWorldMatrix() const override;
		void Translate(DirectX::XMFLOAT3 translation) override;


		DirectX::XMFLOAT3 GetPosition() const override;
		DirectX::XMFLOAT3 GetRotation() const override;
		DirectX::XMFLOAT3 GetScale() const override;

		void SetPosition(DirectX::XMFLOAT3 const& position)override;
		void SetRotation(DirectX::XMFLOAT3 const& rotation)override;
		void SetScale(DirectX::XMFLOAT3 const& scale)override;

	};
}