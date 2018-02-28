#pragma once
#include "IComponent.h"
#include "IGameObject.h"

namespace Glorious
{
	class Component : public IComponent
	{
	public:
		Component(IGameObject* game_object);

	public:
		virtual void Update() override;
		virtual void Awake() override;
		virtual void Start() override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		//virtual void OnCollisionExit() override;

	public:
		template<typename ComponentType>
		ComponentType* GetComponent()const;

	protected:
		IGameObject* m_GameObject;
	};


	template<typename ComponentType>
	ComponentType* Component::GetComponent() const
	{
		return m_GameObject->GetComponent<ComponentType>();
	}

}
