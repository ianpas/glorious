#pragma once

namespace Glorious
{
	class IMesh
	{
	public:
		virtual ~IMesh() = default;

	public:
		virtual int				GetIndexAmount() const = 0;
		virtual int				GetVertexAmount() const = 0;
		virtual Type::Material	GetMaterial() const = 0;
	};
}