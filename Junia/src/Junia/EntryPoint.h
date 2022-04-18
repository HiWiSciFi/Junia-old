#pragma once

#ifdef JE_PLATFORM_WINDOWS

extern Junia::Application* Junia::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Junia::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif