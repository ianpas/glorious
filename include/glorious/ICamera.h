#pragma once

namespace Glorious
{
	class ICamera
	{
	public:
		virtual ~ICamera() = default;

		virtual inline DirectX::XMMATRIX XM_CALLCONV GetViewMatrix()const = 0;
		virtual inline DirectX::XMMATRIX XM_CALLCONV GetProjectionMatrix()const = 0;
		virtual DirectX::XMFLOAT3					 GetEye()const = 0;
		virtual DirectX::XMFLOAT3					 GetFocus()const = 0;

		virtual void								 SetEye(DirectX::XMFLOAT3 const& pos) = 0;
		virtual void								 SetFocus(DirectX::XMFLOAT3 const& pos) = 0;
		virtual void								 SetAspectRatio(float ratio) = 0;
		virtual void								 SetRange(float __near, float __far) = 0;
		virtual void								 SetFovAngle(float angle) = 0; // angle is in radian

	};
}