#include <Junia.h>

class Sandbox : public Junia::Application
{
public:
	Sandbox() = default;
	~Sandbox() override = default;
};

Junia::Application* Junia::CreateApplication()
{
	return new Sandbox();
}
