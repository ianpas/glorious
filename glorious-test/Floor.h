#pragma once

namespace pasha
{
	class Floor :public Glorious::GameObject
	{
	public:
		Floor(Glorious::IScene* scene);

	public:
		void Awake() override;

	};
}