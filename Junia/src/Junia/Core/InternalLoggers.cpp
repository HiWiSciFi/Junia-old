#include "InternalLoggers.hpp"
#include <iostream>

namespace Junia { namespace Log { Logger corelog = Logger("Junia ", &std::cout); } }

namespace Vulkan { namespace Log { Junia::Log::Logger vkLog = Junia::Log::Logger("Vulkan", &std::cout); } }
