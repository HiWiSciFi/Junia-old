#include "Scene1.hpp"
#include <Junia.hpp>

Scene1::Scene1(const std::string& name) : name(name)
{
	Junia::Events::Subscribe<Junia::KeyDownEvent>([ ] (const Junia::KeyDownEvent* e)
		{
			if (e->GetKeyCode() == Junia::KeyCode::ESCAPE) Junia::Window::Get()->Close();
			if (e->GetKeyCode() == Junia::KeyCode::W)
			{
				JMath::iVec2 windowSize = Junia::Window::Get()->GetSize();
				JELOG_INFO << "window size: " << windowSize.x << "x" << windowSize.y;
			}
		});

	/*Junia::Events::Subscribe([ ] (const Junia::Event* e)
		{
			JELOG_INFO << "Event Triggered: " << e->ToString();
		});*/
}

Scene1::~Scene1()
{

}
