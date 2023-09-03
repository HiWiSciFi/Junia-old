#include <Junia.hpp>
#include <chrono>
#include "Scenes/Scene1.hpp"
#include "Systems/GravitySystem.hpp"

int main() {
	try {
		Junia::Init();
		Junia::Renderer::PickDevice(nullptr);

		std::shared_ptr<Junia::Window> window = Junia::Window::Create("Junia Editor");
		Junia::Events::Subscribe<Junia::KeyDownEvent>([ ] (const Junia::KeyDownEvent* event) {
			if (event->GetKeyCode() == Junia::KeyCode::ESCAPE) event->GetWindow()->Close();
		});
		Junia::Events::Subscribe<Junia::WindowClosedEvent>([window] (const Junia::WindowClosedEvent* event) {
			if (event->GetWindow() == window.get()) Junia::StopLoop();
		});
		window->AttachScene(Junia::Scene::Load<Scene1>());

		Junia::RunLoop();
		Junia::Terminate();

	} catch (std::exception& e) {
		Junia::ShowBlockingMessageBox("Junia Editor", e.what(), Junia::MessageBoxIcon::ERROR, Junia::MessageBoxButtons::OK);
	}
	return 0;
}
