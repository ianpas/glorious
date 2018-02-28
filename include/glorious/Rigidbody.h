#pragma once
#include "IRigidbody.h"
#include "Component.h"

namespace Glorious
{
	class Rigidbody :public IRigidbody, public Component
	{
	private:
		std::unique_ptr<btRigidBody>			m_Rigidbody;
		std::unique_ptr<btCollisionShape>		m_CollisionShape;

	public:
		void									Start() override;

		DirectX::XMFLOAT3						GetPosition()const override;
		DirectX::XMFLOAT3						GetRotation()const override;

		void									SetCollisionHandler(IComponent* handler) override;

		void									AddForce(DirectX::XMFLOAT3 force) override;



	public:
		Rigidbody(IGameObject* game_object, btScalar mass, btCollisionShape* collision_shape);
		~Rigidbody();

	};

}
