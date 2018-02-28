#pragma once

namespace pasha
{
	class Player :public Glorious::GameObject
	{
	public:
		Player(Glorious::IScene* scene);

	public:
		void Awake() override;

	};
}