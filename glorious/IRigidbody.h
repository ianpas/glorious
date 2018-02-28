#pragma once
#include "IComponent.h"

namespace Glorious
{
	class IRigidbody
	{
	public:
		virtual ~IRigidbody() = default;

	public:
		virtual DirectX::XMFLOAT3 GetPosition() const = 0;
		virtual DirectX::XMFLOAT3 GetRotation() const = 0;

		virtual void SetCollisionHandler(IComponent* handler) = 0;

		virtual void AddForce(DirectX::XMFLOAT3 force) = 0;
	};
}