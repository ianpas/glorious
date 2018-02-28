#pragma once

namespace pasha
{
	class CameraFollow : public Glorious::Component
	{
	public:
		Glorious::ITransform* m_Target{ nullptr };

	private:
		DirectX::XMFLOAT3 m_Offset;
		Glorious::ICamera* m_Camera{ nullptr };

	public:
		CameraFollow(Glorious::IGameObject* game_object);

	public:
		void Update() override;
		void Start() override;

	};
}