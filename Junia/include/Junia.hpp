#pragma once
#include <Junia/Core/Input.hpp>
#include <Junia/Core/Log.hpp>
#include <Junia/Core/Window.hpp>

#include <Junia/ECS/ECS.hpp>
#include <Junia/ECS/Components.hpp>

#include <Junia/Events/Event.hpp>

namespace Junia
{
	/// @brief Initializes Junia
	void Init();

	/// @brief Terminates Junia
	void Terminate();
}
