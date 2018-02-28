#pragma once

namespace Glorious
{
	class ITransform
	{
	public:
		virtual ~ITransform() = default;

		virtual inline DirectX::XMMATRIX XM_CALLCONV GetWorldMatrix() const = 0;
		virtual void Translate(DirectX::XMFLOAT3 translation) = 0;
		
		virtual DirectX::XMFLOAT3 GetPosition()const = 0;
		virtual DirectX::XMFLOAT3 GetRotation()const = 0;
		virtual DirectX::XMFLOAT3 GetScale()const = 0;

		virtual void SetPosition(DirectX::XMFLOAT3 const& position) = 0;
		virtual void SetRotation(DirectX::XMFLOAT3 const& rotation) = 0;
		virtual void SetScale(DirectX::XMFLOAT3 const& scale)= 0;


	};
}