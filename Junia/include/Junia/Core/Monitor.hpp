#pragma once

#include <cstdint>
#include <string>

namespace Junia
{
	class Monitor
	{
	public:
		virtual ~Monitor() = 0;
		virtual const std::string& GetName() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRedBits() const = 0;
		virtual uint32_t GetGreenBits() const = 0;
		virtual uint32_t GetBlueBits() const = 0;
		virtual uint32_t GetRefreshRate() const = 0;

		static Monitor** GetAll();
		static size_t GetMonitorCount();
		static Monitor* GetPrimary();
	};
}
