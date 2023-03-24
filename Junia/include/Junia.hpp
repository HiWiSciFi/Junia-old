#pragma once

#include <vector>

namespace Junia
{
	/**
	 * @brief Initialize Junia
	*/
	void Init();

	/**
	 * @brief Terminate Junia
	*/
	void Terminate();

	/**
	 * @brief Runs the Junia game loop
	*/
	void RunLoop();

	/**
	 * @brief Stops the Junia game loop
	*/
	void StopLoop();
}

#include "Junia/Core/Input.hpp"
#include "Junia/Core/Log.hpp"
#include <Junia/Core/MessageBox.hpp>
#include "Junia/Core/Window.hpp"

#include "Junia/Renderer/RenderDevice.hpp"
#include "Junia/Renderer/Renderer.hpp"

#include "Junia/ECS/ECS.hpp"
#include "Junia/ECS/Components.hpp"

#include "Junia/Events/Events.hpp"
#include "Junia/Events/InputEvents.hpp"
#include "Junia/Events/WindowEvents.hpp"
