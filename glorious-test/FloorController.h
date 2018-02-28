#pragma once

namespace pasha
{
	class FloorController : public Glorious::Component
	{
	private:
		Glorious::ITransform* m_Transform{ nullptr };
		Glorious::IRigidbody* m_Rigidbody{ nullptr };

	public:
		FloorController(Glorious::IGameObject* game_object);

	public:
		void Start() override;

		void OnCollisionEnter() override;

	};
}