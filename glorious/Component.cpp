#include "stdafx.h"
#include "Component.h"

namespace Glorious
{
	Component::Component(IGameObject* game_object)
	{
		m_GameObject = game_object;
	}

	void Component::Update()
	{

	}

	void Component::Awake()
	{

	}

	void Component::Start()
	{

	}

	void Component::OnCollisionStay()
	{
	}

	void Component::OnCollisionEnter()
	{
	}

	/*void Component::OnCollisionExit()
	{
	}*/


}
