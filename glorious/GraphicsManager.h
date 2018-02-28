#pragma once

namespace Glorious
{
	class GraphicsManager
	{
	public:
		using DeviceContextType = ID3D11DeviceContext;
		using SwapchainType = IDXGISwapChain;

	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_DepthStenilView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState>			m_SamplerState;

	public:
		void												Render(std::function<void()> __render) const;

		float												GetAspectRatio()const;
		float												GetRenderTargetWidth()const;
		float												GetRenderTargetHeight()const;

		template<typename TargetType>
		TargetType*											Get()const;

	public:
		GraphicsManager(GraphicsManager const&) = delete;
		GraphicsManager& operator=(GraphicsManager const&) = delete;
		static GraphicsManager& GetSingleton();

	private:
		GraphicsManager();
		static std::unique_ptr<GraphicsManager> Singleton;
		static std::once_flag OnceFlag;
	};

	template<typename TargetType>
	TargetType* GraphicsManager::Get() const
	{
		auto const& device_manager{ DirectManager::GetSingleton() };
		return device_manager.Get<TargetType>();
	}
}