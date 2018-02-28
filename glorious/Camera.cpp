#include "stdafx.h"
#include "Camera.h"

namespace Glorious
{
	void Camera::Update()
	{
		using namespace Glorious;

		auto camera = GetComponent<ICamera>();
		m_CameraData.m_ViewPos = camera->GetEye();

		auto view = camera->GetViewMatrix();
		view= DirectX::XMMatrixTranspose(view);
		std::memcpy(&m_CameraData.m_View, &view, sizeof(DirectX::XMFLOAT4X3));

		auto proj = camera->GetProjectionMatrix();
		DirectX::XMStoreFloat4x4(&m_CameraData.m_Proj, DirectX::XMMatrixTranspose(proj));

		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };
		device_context->UpdateSubresource(m_cbCamera.Get(), 0, nullptr, &m_CameraData, 0, 0);
	}

	void Camera::Awake()
	{
		SetFovAngle(DirectX::XM_PIDIV4);
		SetRange(0.01f, 1000.f);
		SetEye(DirectX::XMFLOAT3{ 3.f,3.f,3.f });
		SetFocus(DirectX::XMFLOAT3{ 0.f,0.f,0.f });
		SetAspectRatio(GraphicsManager::GetSingleton().GetAspectRatio());

		auto const& device_manager{ DirectManager::GetSingleton() };
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		//
		D3D11_BUFFER_DESC cb_desc;
		std::memset(&cb_desc, 0, sizeof(cb_desc));

		cb_desc.Usage = D3D11_USAGE_DEFAULT;
		cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb_desc.CPUAccessFlags = 0;
		cb_desc.ByteWidth = sizeof(cbCamera);

		m_cbCamera.Attach(device_manager.CreateBuffer(cb_desc, &m_CameraData));

		ID3D11Buffer* pCamera[] = { m_cbCamera.Get() };
		device_context->VSSetConstantBuffers(1, _countof(pCamera), pCamera);
		device_context->PSSetConstantBuffers(1, _countof(pCamera), pCamera);
	}

	Camera::Camera(IGameObject* game_object)
		:Component(game_object)
	{
		Awake();
	}

	void Camera::SetFocus(DirectX::XMFLOAT3 const& pos)
	{
		m_Focus = pos;
	}
	DirectX::XMFLOAT3 Camera::GetFocus() const
	{
		return m_Focus;
	}
	DirectX::XMFLOAT3 Camera::GetEye() const
	{
		return m_Eye;
	}
	void Camera::SetEye(DirectX::XMFLOAT3 const& pos)
	{
		m_Eye = pos;
	}

	void Camera::SetAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
	}

	void Camera::SetRange(float __near, float __far)
	{
		m_Near = __near;
		m_Far = __far;
	}

	void Camera::SetFovAngle(float angle)
	{
		m_FovAngle = angle;
	}

	DirectX::XMMATRIX XM_CALLCONV Camera::GetViewMatrix() const
	{
		return DirectX::XMMatrixLookAtLH
		(
			DirectX::XMLoadFloat3(&m_Eye),
			DirectX::XMLoadFloat3(&m_Focus),
			DirectX::XMVectorSet(0, 1, 0, 0)
		);
	}

	DirectX::XMMATRIX XM_CALLCONV Camera::GetProjectionMatrix() const
	{
		return DirectX::XMMatrixPerspectiveFovLH
		(
			m_FovAngle,
			m_AspectRatio,
			m_Near,
			m_Far
		);

	}
}