#include <Junia.hpp>

class Testapp final : public Junia::Application
{
public:
	Testapp() = default;
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication()
{
	return new Testapp();
}
