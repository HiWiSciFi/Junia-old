#pragma once

#include "Junia/Renderer/RenderDevice.hpp"
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
	 * @brief Get available render devices
	 * @return a reference to a vector containing a list of pointers to valid
	 *         render devices
	*/
	const std::vector<Junia::RenderDevice*>& GetDevices();
}

#include "Junia/Core/Input.hpp"
#include "Junia/Core/Log.hpp"
#include "Junia/Core/Window.hpp"

#include "Junia/ECS/ECS.hpp"
#include "Junia/ECS/Components.hpp"

#include "Junia/Events/Events.hpp"
#include "Junia/Events/InputEvents.hpp"
