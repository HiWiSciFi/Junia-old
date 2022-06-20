#include <Junia.hpp>

class Testapp : public Junia::Application
{
public:
	Testapp() { }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
