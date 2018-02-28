#include "stdafx.h"
#include "Math.h"

DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 const & v1, DirectX::XMFLOAT3 const & v2)
{
	return DirectX::XMFLOAT3{ v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
}

DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 const & v1, DirectX::XMFLOAT3 const & v2)
{
	return DirectX::XMFLOAT3{ v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}

DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 const & v, float value)
{
	return DirectX::XMFLOAT3{ v.x *value,v.y *value,v.z *value };
}

DirectX::XMFLOAT3 operator/(DirectX::XMFLOAT3 const & v, float value)
{
	return DirectX::XMFLOAT3{ v.x / value,v.y / value,v.z / value };
}

DirectX::XMFLOAT3 & operator+=(DirectX::XMFLOAT3 & v, DirectX::XMFLOAT3 const& value)
{
	v.x += value.x;
	v.y += value.y;
	v.z += value.z;
	return v;
}

DirectX::XMFLOAT3 & operator-=(DirectX::XMFLOAT3 & v, DirectX::XMFLOAT3 const & value)
{
	v.x -= value.x;
	v.y -= value.y;
	v.z -= value.z;
	return v;
}

