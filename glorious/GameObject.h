#pragma once
#include "IGameObject.h"
#include "IScene.h"
#include "IComponent.h"

namespace Glorious
{
	class GameObject :public IGameObject
	{
	protected:
		IScene* m_Scene;

	public:
		GameObject(IScene* scene);

	public:
		virtual void Render() override;
		virtual void Update() override;
		virtual void Awake() override = 0;
		virtual void Destroy() override;
	};


}

