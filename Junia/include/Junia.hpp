#pragma once

#include <vector>
#include <Junia/Core/Version.hpp>

namespace Junia {

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

/**
 * @brief Get the current version of the Junia engine
 * @return A Version struct containing the engine version
*/
const Version& GetEngineVersion();

} // namespace Junia

#include "Junia/Core/Input.hpp"
#include "Junia/Core/Log.hpp"
#include "Junia/Core/MessageBox.hpp"
#include "Junia/Core/Window.hpp"
#include "Junia/Core/FileSystem.hpp"

#include "Junia/Renderer/Mesh.hpp"
#include "Junia/Renderer/RenderDevice.hpp"
#include "Junia/Renderer/Renderer.hpp"

#include "Junia/ECS/ECS.hpp"
#include "Junia/ECS/Components.hpp"

#include "Junia/Events/Events.hpp"
#include "Junia/Events/InputEvents.hpp"
#include "Junia/Events/WindowEvents.hpp"
