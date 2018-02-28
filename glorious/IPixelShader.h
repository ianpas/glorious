#pragma once

namespace Glorious
{
	class IPixelShader
	{
	public:
		virtual ~IPixelShader() = default;

		virtual ID3D11PixelShader* GetShader() const = 0;
	};
}
