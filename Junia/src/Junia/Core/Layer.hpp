#pragma once
#include <string>

#include <Junia/Events/Event.hpp>
#include <Junia/Core/Timestep.hpp>

namespace Junia
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name = "Layer") : name(name) { }
		virtual ~Layer() = default;

		virtual void OnEnable() { }
		virtual void OnDisable() { }
		virtual void OnUpdate() { }
		virtual void OnUpdate(const Timestep&) { }

		[[nodiscard]] std::string GetName() const { return name; }

	protected:
		std::string name = "";
	};
}
