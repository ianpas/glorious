#pragma once
#include "IRenderer.h"
#include "Component.h"

namespace Glorious
{
	class cbObject
	{
	public:
		DirectX::XMFLOAT4X4 m_World;
		Type::Material		m_Material;
	};

	class Renderer : public IRenderer, public Component
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>				m_cbObject;
		cbObject										    m_ObjectData;

	public:
		Renderer(IGameObject* game_object);

	public:
		void Render() override;
		void Update() override;
		void Awake() override;

	};
}