#include "stdafx.h"
#include "BulletManager.h"
#include "IComponent.h"

namespace Glorious
{
	std::unique_ptr<BulletManager> BulletManager::Singleton;
	std::once_flag BulletManager::OnceFlag;

	btDiscreteDynamicsWorld * BulletManager::GetPhysicsWorld() const
	{
		return m_DynamicsWorld.get();
	}

	BulletManager& BulletManager::GetSingleton()
	{
		std::call_once(BulletManager::OnceFlag, [&]()
		{
			BulletManager::Singleton.reset(new BulletManager);
		});

		return *BulletManager::Singleton;
	}

	// TODO: change it into memeber function?
	void TickCallback(btDynamicsWorld *world, btScalar timeStep)
	{
		int numManifolds = world->getDispatcher()->getNumManifolds();
		for (int i = 0; i < numManifolds; i++)
		{
			btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();

			std::vector<void*> components
			{
				obA->getUserPointer(),
				obB->getUserPointer()
			};

			/*for (auto each : components)
			{
				if (each)
				{
					auto component = static_cast<IComponent*>(each);
					component->m_CurrentOnCollision = false;

					if (component->m_PreviousOnCollision && !component->m_CurrentOnCollision)
					{
						component->OnCollisionExit();
					}
				}
			}*/

			int numContacts = contactManifold->getNumContacts();
			if (numContacts != 0)
			{
				for (auto each : components)
				{
					if (each)
					{
						auto component = static_cast<IComponent*>(each);
						component->m_CurrentOnCollision = true;

						if (!component->m_PreviousOnCollision && component->m_CurrentOnCollision)
						{
							component->m_PreviousOnCollision = true;
							component->OnCollisionEnter();
						}
						else if (component->m_PreviousOnCollision && component->m_CurrentOnCollision)
						{
							component->OnCollisionStay();
						}
					}
				}



			}

			/*for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance() < 0.f)
				{

					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();
					const btVector3& normalOnB = pt.m_normalWorldOnB;
				}
			}*/
		}
		Debug::Log("Number Manifolds: " + std::to_string(numManifolds));
	}

	BulletManager::BulletManager()
	{
		m_BroadPhase = std::make_unique <btDbvtBroadphase>();
		m_CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
		m_CollisionDispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfiguration.get());
		m_ConstraintSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
		m_DynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(m_CollisionDispatcher.get(), m_BroadPhase.get(), m_ConstraintSolver.get(), m_CollisionConfiguration.get());

		m_DynamicsWorld->setGravity(btVector3(0, -10, 0));
		m_DynamicsWorld->setInternalTickCallback(TickCallback);
	}
}