#include "stdafx.h"
#include "Renderer.h"
#include "IMesh.h"
#include "ITransform.h"
#include "ICamera.h"

namespace Glorious
{
	Renderer::Renderer(IGameObject* game_object)
		:Component(game_object)
	{
		Awake();
	}

	void Renderer::Render()
	{
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };
		//device_context->DrawIndexed(GetComponent<IMesh>()->GetIndexAmount(), 0, 0);
		device_context->Draw(GetComponent<IMesh>()->GetVertexAmount(), 0);
	}

	void Renderer::Update()
	{
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		ID3D11Buffer* pObject[] = { m_cbObject.Get() };
		device_context->VSSetConstantBuffers(0, _countof(pObject), pObject);
		device_context->PSSetConstantBuffers(0, _countof(pObject), pObject);

		// 
		auto world = GetComponent<ITransform>()->GetWorldMatrix();
		DirectX::XMStoreFloat4x4(&m_ObjectData.m_World, DirectX::XMMatrixTranspose(world));

		//
		m_ObjectData.m_Material = GetComponent<IMesh>()->GetMaterial();
		device_context->UpdateSubresource(m_cbObject.Get(), 0, nullptr, &m_ObjectData, 0, 0);
	}

	void Renderer::Awake()
	{
		auto const& device_manager{ DirectManager::GetSingleton() };
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		//
		D3D11_BUFFER_DESC cb_desc;
		std::memset(&cb_desc, 0, sizeof(cb_desc));

		cb_desc.Usage = D3D11_USAGE_DEFAULT;
		cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb_desc.CPUAccessFlags = 0;

		try
		{
			cb_desc.ByteWidth = sizeof(cbObject);
			m_cbObject.Attach(device_manager.CreateBuffer(cb_desc, &m_ObjectData));
		}
		catch (const std::exception& e)
		{

		}
	}

}