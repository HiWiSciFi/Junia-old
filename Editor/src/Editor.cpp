#include <Junia.hpp>
#include <iostream>
#include <chrono>
#include "Scenes/Scene1.hpp"
#include "Systems/GravitySystem.hpp"

#define ENTITY_COUNT 100

int main(int argc, char** argv)
{
	/*try
	{
		Junia::MessageBoxResult result = Junia::ShowMessageBox(
			"Important title",
			"This is an important message!iakuhfiusaehfiuhesuifhuieshfiiwehfuw\nIn another line?",
			Junia::MessageBoxIcon::INFORMATION,
			Junia::MessageBoxButtons::CANCEL_TRYAGAIN_CONTINUE
		);

		switch (result)
		{
		case Junia::MessageBoxResult::NONE:     std::cout << "NONE"     << std::endl; break;
		case Junia::MessageBoxResult::ABORT:    std::cout << "ABORT"    << std::endl; break;
		case Junia::MessageBoxResult::RETRY:    std::cout << "RETRY"    << std::endl; break;
		case Junia::MessageBoxResult::IGNORE:   std::cout << "IGNORE"   << std::endl; break;
		case Junia::MessageBoxResult::TRYAGAIN: std::cout << "TRYAGAIN" << std::endl; break;
		case Junia::MessageBoxResult::CONTINUE: std::cout << "CONTINUE" << std::endl; break;
		case Junia::MessageBoxResult::OK:       std::cout << "OK"       << std::endl; break;
		case Junia::MessageBoxResult::CANCEL:   std::cout << "CANCEL"   << std::endl; break;
		case Junia::MessageBoxResult::YES:      std::cout << "YES"      << std::endl; break;
		case Junia::MessageBoxResult::NO:       std::cout << "NO"       << std::endl; break;
		default: break;
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	return 0;*/

	try
	{
		JELOG_INFO << "Initializing Junia...";
		Junia::Init();

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

		JELOG_INFO << "Loading scenes...";
		Junia::Scene::IdType scene1 = Junia::RegisterScene<Scene1>("Main Scene");
		mainWindow->AttachScene(scene1);
		secondWindow->AttachScene(scene1);
		JELOG_INFO << "Scenes loaded.";

		Junia::Events::Subscribe<Junia::WindowClosedEvent>([mainWindow] (const Junia::WindowClosedEvent* e)
			{
				if (e->GetWindow()->GetId() == mainWindow->GetId()) Junia::StopLoop();
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
	}
	return 0;
}
