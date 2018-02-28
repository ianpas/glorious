#include "stdafx.h"
#include "GameObject.h"
#include "IRenderer.h"
#include "IRigidbody.h"
#include "ITransform.h"

namespace Glorious
{
	GameObject::GameObject(IScene* scene)
	{
		m_Scene = scene;
	}

	void GameObject::Render()
	{
		try
		{
			GetComponent<IRenderer>()->Render();
		}
		catch (const std::exception&)
		{

		}

	}

	void GameObject::Update()
	{
		for (auto& each : m_Components)
		{
			std::call_once(each->m_OnceFlag, [&]()
			{
				each->Start();
			});

			each->Update();
		}

		try
		{
			auto transform = GetComponent<ITransform>();
			auto rigidbody = GetComponent<IRigidbody>();
			transform->SetPosition(rigidbody->GetPosition());
			transform->SetRotation(rigidbody->GetRotation());
		}
		catch (const std::exception&)
		{

		}
	}

	void GameObject::Destroy()
	{
		m_Scene->DestroGameObject(this);
	}

}