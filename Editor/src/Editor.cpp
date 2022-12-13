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

		for (const auto& spair : Junia::ECS::systems)
		{
			spair.second->Update(.0000001f);
		}
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
	virtual void Init() override
	{
		RequireComponent<Transform>();
	}

	virtual void Update(float dt) override
	{
		for (auto const& entity : entities)
		{
			Transform& transform = entity.GetComponent<Transform>();
			transform.z -= 1.0f * dt;
		}
	}
};

int main(int argc, char** argv)
{
	//Junia::Log::log.maxLevel = Junia::Log::LogLevel::Warn;
	//Junia::Log::corelog.maxLevel = Junia::Log::LogLevel::Warn;

	Junia::ECS::RegisterComponent<Transform>();
	Junia::ECS::RegisterSystem<GravitySystem>();

	Junia::ECS::Entity e = Junia::ECS::CreateEntity();
	e.AddComponent<Transform>();

	JELOG_INFO << "Initializing Junia...";
	Junia::Init();
	JELOG_INFO << "Creating Window...";
	RunGame();
	JELOG_INFO << "Terminating Junia...";
	Junia::Terminate();
	JELOG_INFO << "Done.";
	return 0;
}
