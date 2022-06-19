#pragma once
#include <string>

#include <Junia/Events/Event.hpp>

namespace Junia
{
	class Layer
	{
	public:
		explicit Layer(std::string name = "Layer") : name(std::string(name)) { }
		virtual ~Layer() = default;

		virtual void OnEnable() { }
		virtual void OnDisable() { }
		virtual void OnUpdate() { }

		[[nodiscard]] std::string GetName() const { return name; }

	protected:
		std::string name;
	};
}
