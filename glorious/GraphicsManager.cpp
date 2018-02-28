#include "stdafx.h"
#include "GraphicsManager.h"

namespace Glorious
{
	std::unique_ptr<GraphicsManager> GraphicsManager::Singleton;
	std::once_flag GraphicsManager::OnceFlag;

	void GraphicsManager::Render(std::function<void()> __render) const
	{
		auto const& device_context{ Get<ID3D11DeviceContext>() };
		auto const& swapchain{ Get<IDXGISwapChain>() };

		//
		//static float const clear_color[] = { 1.f,1.f,1.f,1.f };
		static float const clear_color[] = { 0.8f,0.8f,0.8f,1.f };
		device_context->ClearRenderTargetView(m_RenderTargetView.Get(), clear_color);
		device_context->ClearDepthStencilView(m_DepthStenilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		__render();

		swapchain->Present(1, 0);
	}

	float GraphicsManager::GetAspectRatio() const
	{
		return GetRenderTargetWidth() / GetRenderTargetHeight();
	}

	float GraphicsManager::GetRenderTargetWidth() const
	{
		return DirectManager::GetSingleton().m_SwapchainDescription.BufferDesc.Width;
	}

	float GraphicsManager::GetRenderTargetHeight() const
	{
		return DirectManager::GetSingleton().m_SwapchainDescription.BufferDesc.Height;
	}

	GraphicsManager& GraphicsManager::GetSingleton()
	{
		std::call_once(GraphicsManager::OnceFlag, [&]()
		{
			GraphicsManager::Singleton.reset(new GraphicsManager);
		});

		return *GraphicsManager::Singleton;
	}

	GraphicsManager::GraphicsManager()
	{
		auto const& device_manager{ DirectManager::GetSingleton() };
		auto const& device_context{ Get<ID3D11DeviceContext>() };

		D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC{ CD3D11_DEFAULT() };
		sampler_desc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		sampler_desc.MaxAnisotropy = 8;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		try
		{
			m_RenderTargetView.Attach(device_manager.CreateView<ID3D11RenderTargetView>(nullptr));
			m_DepthStenilView.Attach(device_manager.CreateView<ID3D11DepthStencilView>(nullptr));
			m_SamplerState.Attach(device_manager.CreateSamplerState(sampler_desc));
		}
		catch (std::exception const& e)
		{
			throw e;
		}

		device_context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStenilView.Get());
		device_context->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());

	}
}