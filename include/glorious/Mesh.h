#pragma once
#include "IMesh.h"
#include "Component.h"

namespace Glorious
{

	class Mesh :public IMesh, public Component
	{
	public:
		Mesh(IGameObject* game_object, std::string const& texture_path, std::string const& mesh_path);

	protected:

		Microsoft::WRL::ComPtr<ID3D11Buffer>				m_VertexBuffer;
		//Microsoft::WRL::ComPtr<ID3D11Buffer>				m_IndexBuffer;,

		int													m_IndexAmount{ 0 };
		int													m_VertexAmount{ 0 };
		Type::Material										m_Material;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_Texture;


	public:
		void												Update() override;

	public:
		int													GetIndexAmount() const override;
		int													GetVertexAmount() const override;
		Type::Material										GetMaterial() const override;

	};

}