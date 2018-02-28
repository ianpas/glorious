#pragma once

namespace pasha
{
	class DirectionalLight :public Glorious::GameObject
	{
	public:
		DirectionalLight(Glorious::IScene* scene);

	public:
		void Awake() override;
	};
}

