#include "Scene1.hpp"
#include <Junia.hpp>

Scene1::Scene1(const std::string& name) : name(name)
{
	Junia::Events::Subscribe<Junia::KeyDownEvent>([ ] (const Junia::KeyDownEvent* e)
		{
			if (e->GetKeyCode() == Junia::KeyCode::ESCAPE)
				e->GetWindow()->Close();
		});

	/*Junia::Events::Subscribe([ ] (const Junia::Event* e)
		{
			JELOG_INFO << "Event Triggered: " << e->ToString();
		});*/
}

Scene1::~Scene1()
{

}
