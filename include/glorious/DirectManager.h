#pragma once

namespace Glorious
{
	class DirectManager
	{
	private:
		//
		D3D_FEATURE_LEVEL									m_FeatureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device>				m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_DeviceContext;

		//
		DXGI_SWAP_CHAIN_DESC								m_SwapchainDescription;
		Microsoft::WRL::ComPtr<IDXGISwapChain>				m_Swapchain;

		//
		HWND												m_WindowHandle;

	public:
		ID3D11InputLayout *									CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC> const& descriptions, std::vector<char> const& shader_file)const;
		ID3D11ShaderResourceView*							CreateShaderResourceView(std::wstring const& texture_path)const;
		ID3D11SamplerState*									CreateSamplerState(D3D11_SAMPLER_DESC const& description)const;

		ID3D11Buffer *										CreateBuffer(D3D11_BUFFER_DESC const& description, void* const& data)const;
		template<typename ShaderType>
		ShaderType*											CreateShader(std::vector<char> const& shader_file, ID3D11ClassLinkage* class_linkage)const;
		template<typename ViewType>
		ViewType*											CreateView(void const* description)const;

	private:
		friend class GraphicsManager;

		template<typename TargetType>
		TargetType*											Get()const;

	public:
		DirectManager(DirectManager const&) = delete;
		DirectManager& operator=(DirectManager const&) = delete;
		static DirectManager& GetSingleton();
		static DirectManager& GetSingleton(HWND handle);

	private:
		DirectManager(HWND handle);
		static std::unique_ptr<DirectManager> Singleton;
		static std::once_flag OnceFlag;
	};


	template<typename ShaderType>
	ShaderType* DirectManager::CreateShader(std::vector<char> const& shader_file, ID3D11ClassLinkage* class_linkage) const
	{
		ShaderType* shader{ nullptr };
		HRESULT result;

		if constexpr (std::is_same<ShaderType, ID3D11VertexShader>::value)
		{
			result = m_Device->CreateVertexShader(shader_file.data(), shader_file.size(), class_linkage, &shader);
		}
		else if constexpr(std::is_same<ShaderType, ID3D11PixelShader>::value)
		{
			result = m_Device->CreatePixelShader(shader_file.data(), shader_file.size(), class_linkage, &shader);
		}

		if (FAILED(result))
		{
			throw std::exception{ "Create Shader Failed." };
		}

		return shader;
	}

	template<typename ViewType>
	ViewType* DirectManager::CreateView(void const* description) const
	{

		ID3D11Texture2D* buffer{ nullptr };
		HRESULT result;

		if constexpr (std::is_same<ViewType, ID3D11RenderTargetView>::value)
		{
			result = m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

			if (FAILED(result))
			{
				throw std::exception{ "Get SwapChainBuffer Failed." };
			}

			ID3D11RenderTargetView* view{ nullptr };
			result = m_Device->CreateRenderTargetView(buffer, static_cast<D3D11_RENDER_TARGET_VIEW_DESC const*>(description), &view);
			buffer->Release();

			if (FAILED(result))
			{
				throw std::exception{ "Create Render Target View Failed." };
			}

			return view;
		}
		else if constexpr (std::is_same<ViewType, ID3D11DepthStencilView>::value)
		{
			D3D11_TEXTURE2D_DESC texture_desc;
			std::memset(&texture_desc, 0, sizeof(texture_desc));
			texture_desc.Width = m_SwapchainDescription.BufferDesc.Width;
			texture_desc.Height = m_SwapchainDescription.BufferDesc.Height;
			texture_desc.MipLevels = 1;
			texture_desc.ArraySize = 1;
			texture_desc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
			texture_desc.SampleDesc = m_SwapchainDescription.SampleDesc;
			texture_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			texture_desc.CPUAccessFlags = 0;
			texture_desc.MiscFlags = 0;

			result = m_Device->CreateTexture2D(&texture_desc, nullptr, &buffer);
			if (FAILED(result))
			{
				throw std::exception{ "Create Depth Stencil Texture Failed." };
			}

			ID3D11DepthStencilView* view{ nullptr };
			result = m_Device->CreateDepthStencilView(buffer, static_cast<D3D11_DEPTH_STENCIL_VIEW_DESC const*>(description), &view);
			if (FAILED(result))
			{
				throw std::exception{ "Create Depth Stencil View Failed." };
			}

			return view;
		}

		return nullptr;

	}

	template<typename TargetType>
	TargetType* DirectManager::Get() const
	{
		if constexpr (std::is_same<TargetType, ID3D11DeviceContext>::value)
		{
			return m_DeviceContext.Get();
		}
		else if constexpr (std::is_same<TargetType, IDXGISwapChain>::value)
		{
			return m_Swapchain.Get();
		}

		return nullptr;
	}
}