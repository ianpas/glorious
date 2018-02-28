#pragma once
#include "IPixelShader.h"
#include "Component.h"


namespace Glorious
{
	class PixelShader : public IPixelShader, public Component
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_PixelShader;

	public:
		PixelShader(std::string const& shader_path, IGameObject* game_object);

	public:
		ID3D11PixelShader * GetShader() const override;


	};
}
