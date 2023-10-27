#include <Junia/Renderer/Surface.hpp>

#include <stdexcept>

namespace Junia {

std::shared_ptr<Surface> Surface::Create(Junia::Window* window, JMath::Vec2ui resolution, VSyncMode vsync) {
	return nullptr;
}

Surface::~Surface() {
}

} // namespace Junia
