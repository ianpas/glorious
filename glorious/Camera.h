#pragma once
#include "ICamera.h"
#include "Component.h"

namespace Glorious
{
	class cbCamera
	{
	public:
		DirectX::XMFLOAT4X3		m_View;
		DirectX::XMFLOAT3		m_ViewPos;
		float					m_Reserved0;
		DirectX::XMFLOAT4X4		m_Proj;
	};

	class Camera :public ICamera, public Component
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_cbCamera;
		Glorious::cbCamera							m_CameraData;

	public:
		void									    Update() override;
		void									    Awake() override;

	private:
		float										m_Far{ 0 };
		float										m_Near{ 0 };
		float										m_FovAngle{ 0 };// Fov: field of view
		float										m_AspectRatio{ 0 };

		DirectX::XMFLOAT3							m_Eye;
		DirectX::XMFLOAT3							m_Focus;

		DirectX::XMFLOAT4X4							m_View;
		DirectX::XMFLOAT4X4							m_Projection;

	public:
		Camera(IGameObject* game_object);

	public:
		inline DirectX::XMMATRIX XM_CALLCONV  GetViewMatrix() const override;
		inline DirectX::XMMATRIX XM_CALLCONV  GetProjectionMatrix() const override;

		DirectX::XMFLOAT3					  GetEye()const override;
		void								  SetEye(DirectX::XMFLOAT3 const & pos) override;

		void								  SetFocus(DirectX::XMFLOAT3 const & pos) override;
		DirectX::XMFLOAT3					  GetFocus()const override;

		void								  SetAspectRatio(float ratio) override;
		void								  SetRange(float __near, float __far) override;
		void								  SetFovAngle(float angle) override;


	};
}
