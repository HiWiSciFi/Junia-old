#include <Junia/Core/Log.hpp>

#include <iostream>

namespace Junia::Log {

Logger log = Logger(" Game ", &std::cout);

} // namespace Junia::Log
