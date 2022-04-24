#pragma once

#include "Junia/Log.hpp"

int main(int argc, char** argv)
{
	Junia::Log::Init();
	JELOG_BASE_INFO("Junia initialized!");

	auto const app = Junia::CreateApplication();
	app->Run();
	delete app;
	return 0;
}