#include <Platform/OpenAL/OpenAL.hpp>
#include <al.h>
#include <alc.h>
#include <iostream>

namespace OpenAL
{
	void Init()
	{
		ALCdevice* device = alcOpenDevice(nullptr);
		if (device == nullptr)
		{
			std::cout << "Could not open device" << std::endl;
		}
	}
}
