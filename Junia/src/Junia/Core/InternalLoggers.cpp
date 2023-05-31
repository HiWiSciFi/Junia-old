#include "InternalLoggers.hpp"
#include <iostream>

namespace Junia { namespace Log { Logger corelog = Logger("Junia ", &std::cout); } }
namespace Vulkan { namespace Log { Junia::Log::Logger vkLog = Junia::Log::Logger("Vulkan", &std::cout); } }
namespace GLFW { namespace Log { Junia::Log::Logger glfwLog = Junia::Log::Logger(" GLFW ", &std::cout); } }
namespace OpenAL { namespace Log { Junia::Log::Logger alLog = Junia::Log::Logger("Audio ", &std::cout); } }
