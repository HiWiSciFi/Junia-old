#include <Junia.hpp>
#include <Junia/UI/JUILayer.hpp>
#include <Junia/Events/EventSystem.hpp>

class ExampleLayer : public Junia::Layer
{
public:
	void OnEnable() override
	{
		Junia::EventSystem::Subscribe(JE_EVENT_BIND_MEMBER_FUNC(OnEvent));
	}

	bool OnEvent(const Junia::Event* e)
	{
		JELOG_INFO("Event: " JELOG_CSTR, e->ToString().c_str());
		return false;
	}
};

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerFront(new ExampleLayer()); PushLayerFront(new Junia::JUILayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
