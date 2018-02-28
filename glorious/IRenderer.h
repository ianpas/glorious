#pragma once

namespace Glorious
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

		virtual void  Render() = 0;

	};
}