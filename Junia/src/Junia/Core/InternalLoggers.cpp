#include "InternalLoggers.hpp"

#include <iostream>

namespace Junia::Log         { Junia::Log::Logger corelog = Junia::Log::Logger("Junia ", &std::cout); }
namespace Junia::Vulkan::Log { Junia::Log::Logger vkLog   = Junia::Log::Logger("Vulkan", &std::cout); }
namespace GLFW::Log          { Junia::Log::Logger glfwLog = Junia::Log::Logger(" GLFW ", &std::cout); }
