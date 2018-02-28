#include "stdafx.h"
#include "FloorController.h"

namespace pasha
{
	FloorController::FloorController(Glorious::IGameObject * game_object)
		:Component(game_object)
	{

	}

	void FloorController::Start()
	{
		m_Transform = GetComponent<Glorious::ITransform>();
		m_Rigidbody = GetComponent<Glorious::IRigidbody>();

		m_Rigidbody->SetCollisionHandler(this);
	}

	void FloorController::OnCollisionEnter()
	{
		//Debug::PopMessageBox("plane collision enter");

		//m_GameObject->DestroyComponent(dynamic_cast<IComponent*>(m_Rigidbody));
		//m_GameObject->Destroy();
	}

}