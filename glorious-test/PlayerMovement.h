#pragma once

namespace pasha
{
	class PlayerMovement : public Glorious::Component
	{
	private:
		Glorious::ITransform* m_Transform{ nullptr };
		Glorious::IRigidbody* m_Rigidbody{ nullptr };

	public:
		PlayerMovement(Glorious::IGameObject* game_object);

	public:
		void Update() override;
		void Start() override;

		void OnCollisionEnter() override;

	};
}