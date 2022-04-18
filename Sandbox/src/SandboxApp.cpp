#include <Junia.h>

class Sandbox : public Junia::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Junia::Application* Junia::CreateApplication()
{
	return new Sandbox();
}
