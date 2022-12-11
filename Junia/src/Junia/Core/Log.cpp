#include "Core.hpp"
#include <Junia/Core/Log.hpp>
#include <iostream>

namespace Junia
{
	namespace Log
	{
		Logger log = Logger("Game", &std::cout);
		Logger corelog = Logger("Junia", &std::cout);
	}
}
