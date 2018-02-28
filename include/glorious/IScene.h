#pragma once
#include "IGameObject.h"

namespace Glorious
{
	class IScene
	{
	protected:
		std::vector<std::shared_ptr<IGameObject>> m_GameObjects;

	public:
		virtual ~IScene() = default;

	public:
		virtual void Render() = 0;

	public:
		template<typename GameObjectType, typename... Args>
		void AddGameObject(Args... args);

		void DestroGameObject(IGameObject* game_object)
		{
			auto to_destroy = m_GameObjects.begin();

			for (auto p = m_GameObjects.begin(); p != m_GameObjects.end(); ++p)
			{
				if (p->get() == game_object)
				{
					to_destroy = p;
				}
			}

			m_GameObjects.erase(to_destroy);
		}

	};

	template<typename GameObjectType, typename ...Args>
	void IScene::AddGameObject(Args ...args)
	{
		m_GameObjects.push_back(std::make_shared<GameObjectType>(args...));
	}
}