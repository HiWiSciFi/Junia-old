#pragma once

#include <iostream>
#include <Junia/Base.hpp>

int main(int argc, char** argv)
{
#ifdef JELOG_EXTENDED_INFO
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Main function called" << "\n");
	JE_ONLY_JELOG_MAX_INFO( std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Running Junia Version [" << Junia::GetCompileVersion() << "] compiled on [" << Junia::Version::GetCompilationDate() << "] at [" << Junia::Version::GetCompilationTime() << "]" << "\n");
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] [at " << __FILE__ << ":" << __LINE__ << "] Initializing Junia..." << std::endl);
#else
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Main function called" << "\n");
	JE_ONLY_JELOG_MAX_INFO( std::cout << "[Junia-preinit] Running Junia Version [" << Junia::GetCompileVersion() << "] compiled on [" << Junia::Version::GetCompilationDate() << "] at [" << Junia::Version::GetCompilationTime() << "]" << "\n");
	JE_ONLY_JELOG_MAX_TRACE(std::cout << "[Junia-preinit] Initializing Junia..." << std::endl);
#endif

	if (!Junia::HeaderCompileVersionMatch())
	{
#ifdef JELOG_EXTENDED_INFO
		JE_ONLY_JELOG_MAX_WARN(std::cout << "[Junia-preinit] POTENTIALLY FATAL [at " << __FILE__ << ":" << __LINE__ << "] Header and Compiled Junia Versions do not match! This could break the application!" << std::endl);
#else
		JE_ONLY_JELOG_MAX_WARN(std::cout << "[Junia-preinit] POTENTIALLY FATAL : Header and Compiled Junia Versions do not match! This could break the application!" << std::endl);
#endif
	}

	Junia::Log::Init();
	JELOG_BASE_INFO("Junia initialized!");

	JELOG_BASE_TRACE("Detected Junia Compile version: {0}", Junia::GetCompileVersion());
	JELOG_BASE_TRACE("Detected Junia Header version:  {0}", Junia::GetHeaderVersion());

	JELOG_BASE_TRACE("Creating user application...");
	auto const app = Junia::CreateApplication();
	JELOG_BASE_TRACE("Running user application...");
	app->Run();
	JELOG_BASE_TRACE("Cleaning user application...");
	delete app;
	JELOG_BASE_TRACE("Done.");
	return 0;
}
