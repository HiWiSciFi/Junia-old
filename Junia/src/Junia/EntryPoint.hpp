#pragma once

#include "Junia/Log.hpp"

int main(int argc, char** argv)
{
	Junia::Log::Init();

	auto const app = Junia::CreateApplication();
	app->Run();
	delete app;
	return 0;
}