#include <Junia.hpp>
#include <Junia/UI/JUILayer.hpp>

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerFront(new Junia::JUILayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
