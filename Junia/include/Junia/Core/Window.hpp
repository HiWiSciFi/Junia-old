#pragma once

#include "../../JMath/Vector2.hpp"
#include "../Renderer/Surface.hpp"
#include "Monitor.hpp"
#include <cstdint>
#include <string>
#include <cstddef>

namespace Junia
{
	enum class WindowFullscreenMode : uint8_t
	{
		WINDOWED              = 0,
		BORDERLESS_FULLSCREEN = 1,
		FULLSCREEN            = 2
	};

	enum class WindowSizeMode : uint8_t
	{
		REGULAR   = 0,
		ICONIFIED = 1,
		MAXIMIZED = 2
	};

	class Window
	{
	public:
		using IdType = int32_t;
		inline IdType GetId() const { return id; }

		static void SwapIds(IdType id1, IdType id2);
		static size_t GetWindowCount();
		static Window** GetAll();
		static bool Exists(IdType id);
		static bool Exists(Window* window);
		static Window* Get(IdType id);
		inline static Window* Get() { return Get(0); }

		static Window* Create(const std::string& title, int width = 800, int height = 600);
		static void Destroy(Window* window);
		static void Destroy(IdType id);
		static void DestroyAll();

	protected:
		IdType id = 0;
		Surface* surface = nullptr;

	public:
		virtual ~Window() = 0;

		virtual void Update() = 0;
		virtual void Close() = 0;

		virtual void* GetNative() const = 0;

		virtual bool IsShown() const = 0;
		virtual void Show() = 0;

		inline bool IsHidden() const { return !IsShown(); }
		virtual void Hide() = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual void SetTitle(const std::string& title) = 0;

		virtual JMath::iVec2 GetPosition() const = 0;
		virtual void SetPosition(JMath::iVec2 position) = 0;

		virtual JMath::iVec2 GetSize() const = 0;
		virtual void SetSize(JMath::iVec2 size) = 0;

		virtual float GetOpacity() const = 0;
		virtual void SetOpacity(float opacity) = 0;

		virtual bool IsFocused() const = 0;
		virtual void RequestFocus() = 0;

		virtual void RequestAttention() = 0;

		virtual WindowSizeMode GetSizeMode() const = 0;
		virtual void SetSizeMode(WindowSizeMode mode) = 0;

		virtual WindowFullscreenMode GetFullscreenMode() const = 0;
		virtual void SetFullscreenMode(WindowFullscreenMode mode, Monitor* monitor = nullptr) = 0;
	};
}
