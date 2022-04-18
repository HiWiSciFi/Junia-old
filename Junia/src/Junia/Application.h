#pragma once

#include "Core.h"

namespace Junia
{
	class JUNIA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}