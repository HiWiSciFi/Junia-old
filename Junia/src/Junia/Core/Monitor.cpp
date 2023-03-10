#include <Junia/Core/Monitor.hpp>

#include <vector>
#include <stdexcept>

namespace Junia
{
	std::vector<Monitor*> monitors{ };

	Monitor::~Monitor()
	{ }

	Monitor** Monitor::GetAll()
	{
		return monitors.data();
	}

	size_t Monitor::GetMonitorCount()
	{
		return monitors.size();
	}

	Monitor* Monitor::GetPrimary()
	{
		if (monitors.size() < 1) throw std::runtime_error("no available monitors");
		return monitors[0];
	}
}
