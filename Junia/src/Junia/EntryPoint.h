#pragma once

#ifdef JE_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	Junia::Log::Init();
	JE_CORE_INFO("Initialized Junia!");

	auto const app = Junia::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif