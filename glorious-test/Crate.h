#pragma once

namespace pasha
{
	class Crate :public Glorious::GameObject
	{
	public:
		Crate(Glorious::IScene* scene);

	public:
		void Awake() override;

	};
}