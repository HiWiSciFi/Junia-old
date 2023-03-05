#pragma once

#include "../../JMath/Vector2.hpp"
#include "../Renderer/Surface.hpp"
#include <cstdint>
#include <string>
#include <cstddef>

namespace Junia
{
	class Window
	{
	public:
		using IdType = int32_t;
		inline IdType GetId() const { return id; }

		static void SwapWindowIds(IdType id1, IdType id2);
		static size_t GetWindowCount();
		static Window** GetWindows();
		static Window* GetWindow(IdType id);
		static bool WindowExists(IdType id);
		static bool WindowExists(Window* window);
		inline static Window* GetWindow() { return GetWindow(0); }

		static Window* Create(const std::string& title, int width = 800, int height = 600);
		static void Destroy(Window* window);
		static void Destroy(IdType id);

	protected:
		IdType id = 0;
		Surface* surface;

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

		virtual void Iconify() = 0;
		virtual void Restore() = 0;
		virtual void Maximize() = 0;
	};
}
