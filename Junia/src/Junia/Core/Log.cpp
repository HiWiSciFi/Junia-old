#include <Junia/Core/Log.hpp>
#include <iostream>

namespace Junia
{
	namespace Log
	{
		Logger log = Logger(" Game ", &std::cout);
	}
}
