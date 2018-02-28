#include "stdafx.h"
#include "Light.h"
#include "ICamera.h"
#include "Transform.h"

namespace Glorious
{
	Light::Light(IGameObject * game_object)
		:Component(game_object)
	{
		Awake();	
	}

	void Light::Update()
	{
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		ID3D11Buffer* pObject[] = { m_cbLight.Get() };
		device_context->VSSetConstantBuffers(2, _countof(pObject), pObject);
		device_context->PSSetConstantBuffers(2, _countof(pObject), pObject);

		m_LightData.m_Pos = GetComponent<ITransform>()->GetPosition();
		device_context->UpdateSubresource(m_cbLight.Get(), 0, nullptr, &m_LightData, 0, 0);
	}

	void Light::Awake()
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
			cb_desc.ByteWidth = sizeof(cbLight);
			m_cbLight.Attach(device_manager.CreateBuffer(cb_desc, &m_LightData));
		}
		catch (const std::exception& e)
		{

		}

		
	}
}