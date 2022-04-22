#include <Junia.h>

class Testapp : public Junia::Application
{
public:
	Testapp() = default;
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication()
{
	return new Testapp();
}
