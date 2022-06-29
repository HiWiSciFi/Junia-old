#pragma once
#include <string>

#include <Junia/Events/Event.hpp>
#include <Junia/Core/Timestep.hpp>

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
		virtual void OnUpdate(Timestep deltaTime) { }

		[[nodiscard]] std::string GetName() const { return name; }

	protected:
		std::string name;
	};
}
