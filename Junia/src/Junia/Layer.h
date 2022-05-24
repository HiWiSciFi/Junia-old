#pragma once
#include <string>

#include "Events/Event.hpp"

namespace Junia
{
	class Layer
	{
	public:
		explicit Layer(std::string name = "Layer") : name(std::move(name)) { }
		virtual ~Layer() = default;

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(const Event*);

		[[nodiscard]] std::string GetName() const { return name; }

	private:
		std::string name;
	};
}
