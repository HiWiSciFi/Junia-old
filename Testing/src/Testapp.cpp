#include <Junia.hpp>
#include <Junia/Events/EventSystem.hpp>

class ExampleLayer final : public Junia::Layer
{
public:
	ExampleLayer() : Layer("Example Layer") { }

	void OnEnable() override
	{
		Junia::EventSystem::Subscribe(JE_EVENT_BIND_MEMBER_FUNC(OnEvent));
		JELOG_INFO("Layer name: {0}", name);
	}

	bool OnEvent(const Junia::Event* e) const
	{
		if (e->GetCategory() != Junia::EventCategory::Window && e->GetType() != Junia::EventType::MouseMove)
			JELOG_TRACE("(Layer) {0}: {1}", name, e->ToString());
		return false;
	}
};

class Testapp final : public Junia::Application
{
public:
	Testapp()
	{
		PushLayerFront(new ExampleLayer());
	}

	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
