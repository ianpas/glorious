#pragma once

namespace Glorious
{
	class BulletManager
	{
	private:
		std::unique_ptr<btBroadphaseInterface>				 m_BroadPhase;
		std::unique_ptr<btDefaultCollisionConfiguration>	 m_CollisionConfiguration;
		std::unique_ptr<btCollisionDispatcher>				 m_CollisionDispatcher;
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_ConstraintSolver;
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_DynamicsWorld;

	public:
		btDiscreteDynamicsWorld* GetPhysicsWorld()const;

	public:
		BulletManager(BulletManager const&) = delete;
		BulletManager& operator=(BulletManager const&) = delete;
		static BulletManager& GetSingleton();

	private:
		BulletManager();
		static std::unique_ptr<BulletManager> Singleton;
		static std::once_flag OnceFlag;
	};
}

