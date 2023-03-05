#include "Editor.hpp"
#include <Junia.hpp>
#include <iostream>
#include <chrono>

void RunGame()
{
	JELOG_INFO << "Creating Windows...";
	Junia::Window* mainWindow = Junia::Window::Create("First Window");
	Junia::Window::Create("Second Window");
	mainWindow->RequestFocus();
	JELOG_INFO << "Windows Created.";

	Junia::Events::Subscribe<Junia::KeyDownEvent>([ ] (const Junia::KeyDownEvent* e)
		{
			if (e->GetKeyCode() == Junia::KeyCode::ESCAPE) Junia::Window::Get()->Close();
		});

	/*Junia::Events::Subscribe([ ] (const Junia::Event* e)
		{
			JELOG_INFO << "Event Triggered: " << e->ToString();
		});*/

	JELOG_INFO << "Running Game loop...";
	while (Junia::Window::Exists(mainWindow))
	{
		Junia::Events::DispatchQueue();

		for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
			Junia::Window::Get(i)->Update();
	}

	JELOG_INFO << "Destroying Windows...";
	Junia::Window::DestroyAll();
}

class GravitySystem : public Junia::ECS::System
{
public:
	virtual void Init() override
	{
		RequireComponent<Junia::Transform>();
	}

	virtual void Update(float dt) override
	{
		for (auto const& e : entities)
		{
			Junia::Transform& transform = e.GetComponent<Junia::Transform>();
			transform.position.z -= 1.0f * dt;
		}
	}
};

constexpr auto ENTITY_COUNT = 100;

int main(int argc, char** argv)
{
	JELOG_INFO << "Initializing Junia...";
	Junia::Init();

	auto starttime = std::chrono::high_resolution_clock::now();
	Junia::ECS::RegisterComponent<Junia::Transform>();
	Junia::ECS::RegisterSystem<GravitySystem>();
	for (Junia::ECS::EntityType i = 0; i < ENTITY_COUNT; i++)
	{
		Junia::ECS::Entity e = Junia::ECS::Entity::Create();
		e.AddComponent<Junia::Transform>();
	}
	for (int i = 0; i < ENTITY_COUNT; i++) Junia::ECS::Entity::Create();
	auto endtime = std::chrono::high_resolution_clock::now();
	float creationtime = std::chrono::duration<float, std::chrono::seconds::period>(endtime - starttime).count();
	JELOG_TRACE << "Entities created! Time: " << creationtime << "s";
	starttime = std::chrono::high_resolution_clock::now();
	for (int i = (ENTITY_COUNT * 2) - 1; i >= 0; i--) Junia::ECS::Entity::Destroy(Junia::ECS::Entity(i));
	endtime = std::chrono::high_resolution_clock::now();
	float destructiontime = std::chrono::duration<float, std::chrono::seconds::period>(endtime - starttime).count();
	JELOG_TRACE << "Entities destroyed! Time: " << destructiontime << "s";

	RunGame();
	JELOG_INFO << "Terminating Junia...";
	Junia::Terminate();
	JELOG_INFO << "Done.";
	return 0;
}
