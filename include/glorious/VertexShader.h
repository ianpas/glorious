#pragma once
#include "IVertexShader.h"
#include "Component.h"

namespace Glorious
{
	class VertexShader : public IVertexShader, public Component
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_InputLayout;

	public:
		VertexShader(std::string const& shader_path, IGameObject* game_object);

	public:
		ID3D11VertexShader* GetShader() const override;


	};
}
