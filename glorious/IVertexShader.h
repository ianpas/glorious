#pragma once

namespace Glorious
{
	class IVertexShader
	{
	public:
		virtual ~IVertexShader() = default;

		virtual ID3D11VertexShader* GetShader() const = 0;
	};
}
