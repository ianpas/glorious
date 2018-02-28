#include "stdafx.h"
#include "DirectManager.h"
#include "..\include\texture\DirectXTex.h"

namespace Glorious
{
	std::unique_ptr<DirectManager> DirectManager::Singleton;
	std::once_flag DirectManager::OnceFlag;

	ID3D11Buffer* DirectManager::CreateBuffer(D3D11_BUFFER_DESC const& description, void * const& data) const
	{
		ID3D11Buffer* buffer{ nullptr };

		D3D11_SUBRESOURCE_DATA data_desc;
		std::memset(&data_desc, 0, sizeof(data_desc));
		data_desc.pSysMem = data;

		auto result{ m_Device->CreateBuffer(&description,&data_desc, &buffer) };
		if (FAILED(result))
		{
			throw std::exception{ "Create Buffer Failed." };
		}

		return buffer;
	}



	ID3D11InputLayout * DirectManager::CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>const & descriptions, std::vector<char> const & shader_file) const
	{
		ID3D11InputLayout* layout{ nullptr };

		auto result{ m_Device->CreateInputLayout(descriptions.data(),static_cast<UINT>(descriptions.size()),shader_file.data(), shader_file.size(), &layout) };

		if (FAILED(result))
		{
			throw std::exception{ "Create Input Layout Failed." };
		}

		return layout;
	}

	ID3D11ShaderResourceView* DirectManager::CreateShaderResourceView(std::wstring const& texture_path) const
	{
		ID3D11ShaderResourceView* view{ nullptr };

		DirectX::TexMetadata meta;
		auto texture = std::make_unique<DirectX::ScratchImage>();
		DirectX::LoadFromTGAFile(texture_path.c_str(), &meta, *texture);

		auto result = DirectX::CreateShaderResourceView(m_Device.Get(), texture->GetImages(), texture->GetImageCount(), meta, &view);

		if (FAILED(result))
		{
			throw std::exception{ "Create Shader Resource View." };
		}

		return view;
	}

	ID3D11SamplerState * DirectManager::CreateSamplerState(D3D11_SAMPLER_DESC const & description) const
	{
		ID3D11SamplerState* state{ nullptr };

		auto result = m_Device->CreateSamplerState(&description, &state);

		if (FAILED(result))
		{
			throw std::exception{ "Create Sampler State Failed." };
		}

		return state;

	}

	DirectManager& DirectManager::GetSingleton()
	{
		return *DirectManager::Singleton;
	}

	DirectManager& DirectManager::GetSingleton(HWND handle)
	{
		std::call_once(DirectManager::OnceFlag, [&]()
		{
			DirectManager::Singleton.reset(new DirectManager{ handle });
		});

		return *DirectManager::Singleton;
	}


	DirectManager::DirectManager(HWND handle)
	{
		m_WindowHandle = handle;

		const D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
		};


		RECT client{};
		GetClientRect(m_WindowHandle, &client);

		std::memset(&m_SwapchainDescription, 0, sizeof(m_SwapchainDescription));
		m_SwapchainDescription.BufferDesc.Width = client.right - client.left;
		m_SwapchainDescription.BufferDesc.Height = client.bottom - client.top;
		m_SwapchainDescription.BufferDesc.RefreshRate.Numerator = 0;
		m_SwapchainDescription.BufferDesc.RefreshRate.Denominator = 0;
		m_SwapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_SwapchainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		m_SwapchainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		m_SwapchainDescription.SampleDesc.Count = 8;
		m_SwapchainDescription.SampleDesc.Quality = 0;
		m_SwapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		m_SwapchainDescription.BufferCount = 1;
		m_SwapchainDescription.OutputWindow = m_WindowHandle;
		m_SwapchainDescription.Windowed = TRUE;
		m_SwapchainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		m_SwapchainDescription.Flags = 0;

		auto result{ D3D11CreateDeviceAndSwapChain
		(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_SINGLETHREADED,
			feature_levels,
			_countof(feature_levels),
			D3D11_SDK_VERSION,
			&m_SwapchainDescription,
			&m_Swapchain,
			&m_Device,
			&m_FeatureLevel,
			&m_DeviceContext
		) };

		if (FAILED(result))
		{
			throw std::exception{ "Initialize D3D11 Failed," };
		}
	}
}