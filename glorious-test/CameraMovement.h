#pragma once

namespace pasha
{
	class CameraMovement : public Glorious::Component
	{
	private:
		Glorious::ITransform* m_Transform{ nullptr };
		Glorious::ICamera* m_Camera{ nullptr };

	public:
		CameraMovement(Glorious::IGameObject* game_object);

	public:
		void Update() override;
		void Start() override;

	};
}