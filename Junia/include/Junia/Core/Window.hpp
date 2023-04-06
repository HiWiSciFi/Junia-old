#pragma once

#include "../../JMath/Vector2.hpp"
#include "../Renderer/Surface.hpp"
#include "Monitor.hpp"
#include "Scene.hpp"
#include <cstdint>
#include <string>

namespace Junia
{
	constexpr int DEFAULT_WIDTH = 800;
	constexpr int DEFAULT_HEIGHT = 600;

	/**
	 * @brief The Fullscreen states a window can go into
	*/
	enum class WindowFullscreenMode : uint8_t
	{
		WINDOWED              = 0,
		BORDERLESS_FULLSCREEN = 1,
		FULLSCREEN            = 2
	};

	/**
	 * @brief The size states a window can go into
	*/
	enum class WindowSizeMode : uint8_t
	{
		REGULAR   = 0,
		ICONIFIED = 1,
		MAXIMIZED = 2
	};

	/**
	 * @brief A wrapper class for platform-specific window handles
	*/
	class Window
	{
	public:
		/**
		 * @brief The type to use for IDs for windows
		*/
		using IdType = int32_t;

		/**
		 * @brief Get the id of the window
		 * @return The ID of the window
		*/
		[[nodiscard]] inline IdType GetId() const { return id; }

		/**
		 * @brief Swap IDs of two windows (mainly for internal use)
		 * @param id1 The ID of the first window
		 * @param id2 The ID of the second window
		*/
		static void SwapIds(IdType id1, IdType id2);

		/**
		 * @brief Get the overall amount of windows that have been created
		 * @return The amount of windows that have been created
		*/
		static size_t GetWindowCount();

		/**
		 * @brief Get a pointer to an array of all windows that have been
		 *        created (see GetWindowCount() for the length of the array)
		 * @return A pointer to the start of an array of window pointers
		*/
		static Window** GetAll();

		/**
		 * @brief Get if a window with a specific ID exists
		 * @param id The ID of the window to check for
		 * @return True if it does exist, false otherwise
		*/
		static bool Exists(IdType windowId);

		/**
		 * @brief Get if a window exists (if the passed pointer is valid)
		 * @param window a pointer to the window
		 * @return True if it is a valid pointer, false otherwise
		*/
		static bool Exists(Window* window);

		/**
		 * @brief Get a window by its ID
		 * @param id The ID of the window to get
		 * @return A pointer to a Window with the ID or nullptr if it doesn't
		 *         exist
		*/
		static Window* Get(IdType windowId);

		/**
		 * @brief Get the currently focused window
		 * @return A pointer to the window or a nullptr if no windows of this
		 *         application currently have input focus
		*/
		inline static Window* Get() { return Get(0); }

		/**
		 * @brief Create a window
		 * @param title The title of the window
		 * @param width The initial width of the window
		 * @param height The initial height of the window
		 * @return A pointer to the newly created window
		*/
		static Window* Create(const std::string& title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

		/**
		 * @brief Destroy a window (WARNING: THIS IS VERY UNSAFE -
		 *        Junia::Window::Close() is preferred)
		 * @param window A pointer to the window to destroy
		*/
		static void Destroy(Window* window);

		/**
		 * @brief Destroy a window (WARNING: THIS IS VERY UNSAFE -
		 *        Junia::Window::Close() is preferred)
		 * @param id The ID of the window to destroy
		*/
		static void Destroy(IdType windowId);

		/**
		 * @brief Destroy all windows
		*/
		static void DestroyAll();

	protected:
		// TODO(HiWiSciFi): Move to getter -> make variable private [05-Apr-23]
		/**
		 * @brief The ID of the window
		*/
		IdType id = 0;

		// TODO(HiWiSciFi): No need for this to be here (move to api) [05-Apr-23]
		/**
		 * @brief A pointer to the render API Surface of this window
		*/
		Surface* surface = nullptr;

	public:
		virtual ~Window() = 0;

		/**
		 * @brief Update the window
		*/
		virtual void Update() = 0;

		/**
		 * @brief Close the window gracefully
		*/
		virtual void Close() = 0;

		/**
		 * @brief Get the WindowAPI native handle to the window
		 * @return A Handle for the window
		*/
		[[nodiscard]] virtual void* GetNative() const = 0;

		/**
		 * @brief Get if the window is currently being shown
		 * @return True if it is shown, false otherwise
		*/
		[[nodiscard]] virtual bool IsShown() const = 0;

		/**
		 * @brief Show the window
		*/
		virtual void Show() = 0;

		/**
		 * @brief Get if the window is currently being hidden
		 * @return True if it is hidden, false otherwise
		*/
		[[nodiscard]] inline bool IsHidden() const { return !IsShown(); }

		/**
		 * @brief Hide the window
		*/
		virtual void Hide() = 0;

		/**
		 * @brief Get the title of the window
		 * @return A reference to a string containing the title
		*/
		[[nodiscard]] virtual const std::string& GetTitle() const = 0;

		/**
		 * @brief Set the title of the window
		 * @param title The new title to set for the window
		*/
		virtual void SetTitle(const std::string& title) = 0;

		/**
		 * @brief Get the position of the window on the screen
		 * @return A Vector containing the window position
		*/
		[[nodiscard]] virtual JMath::Vec2i GetPosition() const = 0;

		/**
		 * @brief Set the position of the window on the screen
		 * @param position The position to move the window to
		*/
		virtual void SetPosition(JMath::Vec2i position) = 0;

		/**
		 * @brief Get the size of the window (excluding window decorations)
		 * @return A Vector containing the size along the x and y axes of the
		 *         window
		*/
		[[nodiscard]] virtual JMath::Vec2i GetSize() const = 0;

		/**
		 * @brief Set the size of the window (anchor: top left window corner)
		 * @param size The size to scale the window to
		*/
		virtual void SetSize(JMath::Vec2i size) = 0;

		/**
		 * @brief Get the size of the framebuffer in pixels
		 * @return A Vector containing the size of the framebuffer
		*/
		[[nodiscard]] virtual JMath::Vec2ui GetFramebufferSize() const = 0;

		/**
		 * @brief Get the opacity of the window
		 * @return The opacity of the window (1.0 <= value >= 0.0)
		*/
		[[nodiscard]] virtual float GetOpacity() const = 0;

		/**
		 * @brief Set the opacity of the window
		 * @param opacity The opacity to set the window to
		*/
		virtual void SetOpacity(float opacity) = 0;

		/**
		 * @brief Get if the window has input focus
		 * @return True if it foes, false otherwise
		*/
		[[nodiscard]] virtual bool IsFocused() const = 0;

		/**
		 * @brief Request input focus for the window (not necessarily supported
		 *        on all platforms). This may pull the user focus away from
		 *        another window. Consider using
		 *        Junia::Window::RequestAttention() if you just want to signal
		 *        the user.
		*/
		virtual void RequestFocus() = 0;

		/**
		 * @brief Request user attention to the window
		*/
		virtual void RequestAttention() = 0;

		/**
		 * @brief Get if the window is iconified or maximized
		 * @return The current size mode of the window
		*/
		[[nodiscard]] virtual WindowSizeMode GetSizeMode() const = 0;

		/**
		 * @brief Iconify, Maximize or Reset the window
		 * @param mode The mode to set the window to
		*/
		virtual void SetSizeMode(WindowSizeMode mode) = 0;

		/**
		 * @brief Get the current fullscreen mode of the window
		 * @return The current fullscreen mode
		*/
		[[nodiscard]] virtual WindowFullscreenMode GetFullscreenMode() const = 0;

		/**
		 * @brief Set the fullscreen mode of the window
		 * @param mode The mode to set the window to
		 * @param monitor The monitor to use for fullscreen (ignored when mode =
		 *                WindowFullscreenMode::WINDOWED) or nullptr to use the
		 *                default monitor. See Junia::Monitor::GetAll() for a
		 *                list of monitors.
		*/
		virtual void SetFullscreenMode(WindowFullscreenMode mode, Monitor* monitor = nullptr) = 0;

		/**
		 * @brief Attach a scene to this window
		 * @param sceneId The ID of the scene to attach (see
		 *                Junia::RegisterScene())
		*/
		virtual void AttachScene(Scene::IdType sceneId) = 0;
	};
} // namespace Junia
