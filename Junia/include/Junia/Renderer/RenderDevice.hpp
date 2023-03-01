#pragma once

#include <cstdint>

namespace Junia
{
	enum class RenderDeviceType : uint8_t
	{
		OTHER          = 0,
		CPU            = 1,
		INTEGRATED_GPU = 2,
		VIRTUAL_GPU    = 3,
		DISCRETE_GPU   = 4
	};

	class RenderDevice
	{
	protected:
		RenderDeviceType type = RenderDeviceType::OTHER;
		uint32_t rating = 0;

	public:
		virtual ~RenderDevice() = 0;
		virtual void Pick() = 0;
		inline RenderDeviceType GetType() const { return type; }
		inline uint32_t GetRating() const { return rating; }
		virtual const char* GetName() const = 0;
	};
}
