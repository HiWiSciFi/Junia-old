#include <Junia.hpp>
#include <chrono>

#include "Scenes/Scene1.hpp"
#include "Systems/GravitySystem.hpp"

int main() {
	try {
		// Initialize Junia
		Junia::Init("Junia Editor", Junia::Version(1, 0, 0));

		// Select render device
		const std::vector<std::shared_ptr<Junia::RenderDevice>> renderDevices = Junia::Renderer::GetDevices();
		JELOG_INFO << "Render Devices:";
		for (const auto& device : renderDevices) JELOG_INFO << "  - " << device->GetName();
		Junia::Renderer::PickDevice(nullptr);

		// Create window
		std::shared_ptr<Junia::Window> window = Junia::Window::Create("Junia Editor");

		// Register event callbacks
		Junia::Events::Subscribe<Junia::KeyDownEvent>([ ] (const Junia::KeyDownEvent* event) {
			if (event->GetKeyCode() == Junia::KeyCode::ESCAPE) event->GetWindow()->Close();
		});
		Junia::Events::Subscribe<Junia::WindowClosedEvent>([window] (const Junia::WindowClosedEvent* event) {
			if (event->GetWindow() == window.get()) Junia::StopLoop();
		});

		// Load scene
		window->AttachScene(Junia::Scene::Load<Scene1>());

		// Run Loop
		Junia::RunLoop();

		// Cleanup
		Junia::Terminate();

	} catch (std::exception& e) {
		// Prompt user with error
		Junia::ShowBlockingMessageBox("Junia Editor", e.what(), Junia::MessageBoxIcon::ERROR, Junia::MessageBoxButtons::OK);
	}
	return 0;
}
