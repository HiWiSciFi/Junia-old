#pragma once
#include <string>

#include <Junia/Events/Event.hpp>

namespace Junia
{
	class Layer
	{
	public:
		explicit Layer(std::string name = "Layer") : name(std::move(name)) { }
		virtual ~Layer() = default;

		virtual void OnEnable();
		virtual void OnDisable();
		virtual void OnUpdate();
		virtual void OnEvent(const Event*);

		std::string GetName() const { return name; }

	private:
		std::string name;
	};
}
