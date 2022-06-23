#include <Junia.hpp>
#include <Junia/UI/ImGuiLayer.hpp>

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerFront(new Junia::ImGuiLayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
