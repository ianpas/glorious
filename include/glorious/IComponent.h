#pragma once

namespace Glorious
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;

	public:
		virtual void Update() = 0;
		virtual void Awake() = 0;
		virtual void Start() = 0;

		virtual void OnCollisionEnter() = 0;
		virtual void OnCollisionStay() = 0;
		//virtual void OnCollisionExit() = 0;

	public:
		std::once_flag m_OnceFlag;

		bool		   m_PreviousOnCollision{ false };
		bool		   m_CurrentOnCollision{ false };
	};
}