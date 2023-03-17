#pragma once

#include "../../JMath/Vector2.hpp"
#include "../../JMath/Vector3.hpp"
#include <cstdint>
#include <string>

namespace Junia
{
	class Monitor
	{
	public:
		virtual ~Monitor() = 0;
		virtual const std::string& GetName() const = 0;
		virtual JMath::uiVec2 GetPosition() const = 0;
		virtual JMath::uiVec2 GetSize() const = 0;
		virtual JMath::uiVec3 GetColorBits() const = 0;
		virtual uint32_t GetRefreshRate() const = 0;
		virtual void* GetNative() const = 0;

		static Monitor** GetAll();
		static size_t GetMonitorCount();
		static Monitor* GetPrimary();
	};
}
