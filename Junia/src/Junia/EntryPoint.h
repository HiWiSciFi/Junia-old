#pragma once

#ifdef JE_PLATFORM_WINDOWS

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
	Junia::Log::Init();
	JE_CORE_WARN("Initialized Log!");
	int a = 5;
	JE_INFO("Hello! Var={0}", a);

	auto const app = Junia::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif