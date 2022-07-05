#pragma once

#include <Junia/Events/Event.hpp>

namespace Junia
{
	class JUI
	{
	public:
		static void Init();

		static void Begin();
		static void End();

		static void Shutdown();

		static void Text(const std::string& text);

	private:
		static bool OnEvent(const Event* e);
	};
}
