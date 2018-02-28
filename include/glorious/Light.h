#pragma once
#include "ILight.h"
#include "Component.h"

namespace Glorious
{
	class cbLight
	{
	public:
		DirectX::XMFLOAT3   m_Pos;
		float				m_Reserved0;
	};

	class Light :public ILight, public Component
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>				m_cbLight;
		cbLight												m_LightData;

	public:
		Light(IGameObject* game_object);

	public:
		void Update() override;
		void Awake() override;

	};
}
