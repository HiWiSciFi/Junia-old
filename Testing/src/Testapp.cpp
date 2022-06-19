#include <Junia.hpp>
#include <Junia/Events/EventSystem.hpp>
#include <cstdarg>

class ExampleLayer final : public Junia::Layer
{
public:
	ExampleLayer() : Layer("Example Layer") { }

	void OnEnable() override
	{
		Junia::EventSystem::Subscribe(JE_EVENT_BIND_MEMBER_FUNC(OnEvent));
		JELOG_TRACE("Layer name: " JELOG_CSTR, name.c_str());
	}

	bool OnEvent(const Junia::Event* e) const
	{
		if (e->GetCategory() != Junia::EventCategory::Window && e->GetType() != Junia::EventType::MouseMove)
			JELOG_TRACE("(Layer) " JELOG_CSTR ": " JELOG_CSTR, name.c_str(), e->ToString().c_str());
		return false;
	}
};

class Testapp : public Junia::Application
{
public:
	Testapp()
	{
		PushLayerFront(new ExampleLayer());
	}

	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
