#include "stdafx.h"
#include "Rigidbody.h"
#include "ITransform.h"

namespace Glorious
{

	Rigidbody::Rigidbody(IGameObject* game_object, btScalar mass, btCollisionShape* collision_shape)
		:Component(game_object)
	{
		m_CollisionShape.reset(collision_shape);

		btVector3 inertia{};
		m_CollisionShape->calculateLocalInertia(mass, inertia);

		btRigidBody::btRigidBodyConstructionInfo rigidbody_info{ mass, nullptr, m_CollisionShape.get(), inertia };

		m_Rigidbody = std::make_unique<btRigidBody>(rigidbody_info);

		auto physics_world = BulletManager::GetSingleton().GetPhysicsWorld();
		physics_world->addRigidBody(m_Rigidbody.get());
	}

	Rigidbody::~Rigidbody()
	{
		BulletManager::GetSingleton().GetPhysicsWorld()->removeRigidBody(m_Rigidbody.get());
	}

	void Rigidbody::AddForce(DirectX::XMFLOAT3 force)
	{
		m_Rigidbody->applyCentralForce(btVector3{ force.x,force.y,force.z });
	}



	void Rigidbody::Start()
	{
		auto transform = GetComponent<ITransform>();

		auto to_radian = [&](float degree)
		{
			return (degree*DirectX::XM_PI) / 180.f;
		};

		btQuaternion rotation{ to_radian(transform->GetRotation().x), to_radian(transform->GetRotation().y),to_radian(transform->GetRotation().z) };
		btVector3 position{ transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z };

		m_Rigidbody->setWorldTransform(btTransform(rotation, position));


	}

	DirectX::XMFLOAT3 Rigidbody::GetPosition() const
	{

		btTransform transform{ m_Rigidbody->getWorldTransform() };
		Debug::Log("y: " + std::to_string(transform.getOrigin().getY()));

		return DirectX::XMFLOAT3{ transform.getOrigin().getX(),transform.getOrigin().getY(),transform.getOrigin().getZ() };
	}

	DirectX::XMFLOAT3 Rigidbody::GetRotation() const
	{
		btTransform transform{ m_Rigidbody->getWorldTransform() };

		btScalar z{};
		btScalar y{};
		btScalar x{};
		transform.getBasis().getEulerZYX(z, y, x);

		auto to_degree = [&](float radian)
		{
			return (radian * 180.f) / DirectX::XM_PI;
		};

		return DirectX::XMFLOAT3{ to_degree(x) , to_degree(y) , to_degree(z) };
	}

	void Rigidbody::SetCollisionHandler(IComponent * handler)
	{
		m_Rigidbody->setUserPointer(handler);
	}
}
