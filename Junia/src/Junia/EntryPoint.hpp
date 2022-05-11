#pragma once

#include "Junia/Log.hpp"
#include "Junia/Version.hpp"
#include <iostream>

#include "Events/Events.hpp"
#include "Events/MouseEvents.hpp"

bool HandleMouseEvent(const Junia::Event* e)
{
	if (e->GetType() != Junia::EventType::MouseMoveEvent) return false;
	const auto ev = reinterpret_cast<const Junia::MouseMoveEvent*>(e);
	JELOG_INFO("Event handled: {0} with coords: {1}, {2}", e->ToString(), ev->x, ev->y);
	return true;
}

int main(int argc, char** argv)
{
#ifdef JELOG_EXTENDED_INFO
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Main function called" << std::endl);
	JE_ONLY_JELOG_MAX_INFO( std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Running Junia Version [" << Junia::Version::GetMajor() << "." << Junia::Version::GetMinor() << "." << Junia::Version::GetPatch() << "] compiled on [" << Junia::Version::GetCompilationDate() << "] at [" << Junia::Version::GetCompilationTime() << "]" << std::endl);
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Initializing Junia..." << std::endl);
#else
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Main function called" << std::endl);
	JE_ONLY_JELOG_MAX_INFO( std::cout << "[Junia-preinit] Running Junia Version [" << Junia::Version::GetMajor() << "." << Junia::Version::GetMinor() << "." << Junia::Version::GetPatch() << "] compiled on [" << Junia::Version::GetCompilationDate() << "] at [" << Junia::Version::GetCompilationTime() << "]" << std::endl);
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Initializing Junia..." << std::endl);
#endif

	Junia::Log::Init();
	JELOG_BASE_INFO("Junia initialized!");


	JELOG_INFO("Registering EventListener...");
	Junia::EventSystem::Subscribe(HandleMouseEvent);
	JELOG_INFO("Triggering Event...");
	Junia::EventSystem::TriggerImmediate(new Junia::MouseMoveEvent(10, 100));


	JELOG_BASE_TRACE("Creating user application...");
	auto const app = Junia::CreateApplication();
	JELOG_BASE_TRACE("Running user application...");
	app->Run();
	JELOG_BASE_TRACE("Cleaning user application...");
	delete app;
	JELOG_BASE_TRACE("Done.");
	return 0;
}
