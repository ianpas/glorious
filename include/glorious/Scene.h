#pragma once
#include "IScene.h"

namespace Glorious
{
	class Scene :public IScene
	{
	protected:
		D3D11_VIEWPORT							  m_ViewPort;

	public:
		Scene();

	public:
		void Render() override;

	private:
		void OnRender();
	};


}