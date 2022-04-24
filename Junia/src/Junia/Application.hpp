#pragma once

#include "Base.hpp"

namespace Junia
{
	class JE_API_IO Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}