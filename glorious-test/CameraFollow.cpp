#include "stdafx.h"
#include "CameraFollow.h"

namespace pasha
{
	CameraFollow::CameraFollow(Glorious::IGameObject * game_object)
		:Component(game_object)
	{

	}

	void CameraFollow::Start()
	{

		m_Camera = GetComponent<Glorious::ICamera>();
		m_Offset = m_Target->GetPosition() - m_Camera->GetEye();
	}

	void CameraFollow::Update()
	{

		auto eye = m_Target->GetPosition() - m_Offset;
		auto transform = eye - m_Camera->GetEye();

		m_Camera->SetEye(eye);

		auto focus = m_Camera->GetFocus() + transform;
		m_Camera->SetFocus(focus);


	}


}