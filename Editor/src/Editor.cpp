#include <Junia.hpp>
#include <chrono>
#include "Scenes/Scene1.hpp"
#include "Systems/GravitySystem.hpp"

#define ENTITY_COUNT 100

int main(int argc, char** argv)
{
	try
	{
		JELOG_INFO << "Initializing Junia...";
		Junia::Init();
		Junia::Renderer::PickDevice(nullptr);

		auto starttime = std::chrono::high_resolution_clock::now();
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

		JELOG_INFO << "Creating Windows...";
		Junia::Window* mainWindow = Junia::Window::Create("First Window");
		Junia::Window* secondWindow = Junia::Window::Create("Second Window");
		mainWindow->RequestFocus();
		JELOG_INFO << "Windows created.";

		/*JELOG_INFO << "Loading scenes...";
		Junia::Scene::IdType scene1ID = Junia::RegisterScene<Scene1>("Main Scene");
		std::shared_ptr<Junia::Scene> scene1 = Junia::Scene::Load(scene1ID);
		mainWindow->AttachScene(scene1);
		secondWindow->AttachScene(scene1);
		JELOG_INFO << "Scenes loaded.";*/

		Junia::Events::Subscribe<Junia::KeyDownEvent>([mainWindow] (const Junia::KeyDownEvent* e)
			{
				if (e->GetKeyCode() == Junia::KeyCode::ESCAPE)
					e->GetWindow()->Close();
			});

		Junia::Events::Subscribe<Junia::WindowClosedEvent>([mainWindow] (const Junia::WindowClosedEvent* e)
			{
				if (e->GetWindow() == mainWindow) Junia::StopLoop();
			});

		JELOG_INFO << "Running Game loop...";
		Junia::RunLoop();

		JELOG_INFO << "Terminating Junia...";
		Junia::Terminate();
		JELOG_INFO << "Done.";
	}
	catch (std::exception e)
	{
		JELOG_CRITICAL << "Exception thrown: " << e.what();
		Junia::ShowBlockingMessageBox(
			"Junia Editor",
			e.what(),
			Junia::MessageBoxIcon::ERROR,
			Junia::MessageBoxButtons::OK
		);
	}
	return 0;
}
