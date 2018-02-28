#pragma once

namespace pasha
{
	class MainCamera :public Glorious::GameObject
	{
	public:
		MainCamera(Glorious::IScene* scene);

	public:
		void Awake() override;
	};
}

