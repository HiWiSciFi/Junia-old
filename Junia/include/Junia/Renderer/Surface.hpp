#pragma once

#include "Mesh.hpp"
#include "Material.hpp"
#include "RenderPackage.hpp"
#include <memory>

namespace Junia {

class Window;

/**
 * @brief A wrapper for RenderAPI Surfaces to render to
*/
class Surface {
public:
	enum class VSyncMode : uint8_t {
		/**
		 * @brief Immediate presentation after rendering
		*/
		OFF = 0,
		/**
		 * @brief Wait for V-Blank to present image
		*/
		ON_QUEUE = 1,
		/**
		 * @brief Don't wait for next V-Blank if late
		*/
		ON_QUEUE_RELAXED = 2,
		/**
		 * @brief Replace old frames with newer ones once ready
		*/
		ON_QUEUE_REPLACE = 3
	};

public:
	/**
	 * @brief Create a new Surface from a window
	 * @param window a pointer the window this surface will be created for
	 * @return a pointer to the created window
	*/
	static std::shared_ptr<Surface> Create(Window* window, JMath::Vec2ui resolution, VSyncMode vsync);

	virtual ~Surface() = 0;

	virtual JMath::Vec2ui GetResolution() = 0;
	virtual VSyncMode GetVSyncMode() = 0;

	/**
	 * @brief Call when the framebuffer has been resized so that the surface
	 *        etc. can be updated (optional, in case the resize is not
	 *        triggered automatically)
	*/
	virtual void FramebufferResized(JMath::Vec2ui newSize) = 0;

	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;

	/**
	 * @brief Draw a test triangle TODO: replace with proper API
	*/
	virtual void Draw(std::shared_ptr<Junia::RenderPackage> package) = 0;
};

} // namespace Junia
