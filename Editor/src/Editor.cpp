#include "Editor.hpp"
#include <Junia.hpp>
#include <iostream>

void RunGame()
{
	Junia::Window* mainWindow = Junia::Window::Create("First Window");
	mainWindow->Open();
	Junia::Window::Create("Second Window")->Open();
	mainWindow->Focus();

	while (mainWindow->IsOpen())
	{
		for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
			Junia::Window::GetWindow(i)->Update();

		if (Junia::Input::IsKeyDown(Junia::KeyCode::ESCAPE))
			Junia::Window::GetWindow()->Close();
	}

	Junia::Window** const windows = Junia::Window::GetWindows();
	for (Junia::Window::IdType i = Junia::Window::GetWindowCount(); i > 0; i--)
		Junia::Window::Destroy(windows[i]);
}

struct Transform
{
	float x, y, z;
};

class GravitySystem : public Junia::ECS::System
{
public:
	virtual void Init() override
	{
		RequireComponent<Transform>();
	}

	virtual void Update(float dt) override
	{
		for (auto const& e : entities)
		{
			Transform& transform = e.GetComponent<Transform>();
			transform.z -= 1.0f * dt;
		}
	}
};

#define ENTITY_COUNT (1000000)

#include <chrono>

int main(int argc, char** argv)
{
	auto starttime = std::chrono::high_resolution_clock::now();
	Junia::ECS::RegisterComponent<Transform>();
	Junia::ECS::RegisterSystem<GravitySystem>();
	for (Junia::ECS::EntityType i = 0; i < ENTITY_COUNT; i++)
	{
		Junia::ECS::Entity e = Junia::ECS::Entity::Create();
		e.AddComponent<Transform>();
	}
	for (int i = 0; i < ENTITY_COUNT; i++) Junia::ECS::Entity::Create();
	auto endtime = std::chrono::high_resolution_clock::now();
	float creationtime = std::chrono::duration<float, std::chrono::seconds::period>(endtime - starttime).count();
	JELOG_WARN << "Entities created! Time: " << creationtime << "s";
	starttime = std::chrono::high_resolution_clock::now();
	for (int i = (ENTITY_COUNT * 2) - 1; i >= 0; i--) Junia::ECS::Entity::Destroy(Junia::ECS::Entity(i));
	endtime = std::chrono::high_resolution_clock::now();
	float destructiontime = std::chrono::duration<float, std::chrono::seconds::period>(endtime - starttime).count();
	JELOG_WARN << "Entities destroyed! Time: " << destructiontime << "s";

	JELOG_INFO << "Initializing Junia...";
	Junia::Init();
	JELOG_INFO << "Creating Window...";
	RunGame();
	JELOG_INFO << "Terminating Junia...";
	Junia::Terminate();
	JELOG_INFO << "Done.";
	return 0;
}
