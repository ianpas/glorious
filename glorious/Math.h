#pragma once

DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 const& v1, DirectX::XMFLOAT3 const& v2);
DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 const& v1, DirectX::XMFLOAT3 const& v2);
DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 const& v, float value);
DirectX::XMFLOAT3 operator/(DirectX::XMFLOAT3 const& v, float value);

DirectX::XMFLOAT3& operator+=(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3 const& value);
DirectX::XMFLOAT3& operator-=(DirectX::XMFLOAT3& v, DirectX::XMFLOAT3 const& value);

