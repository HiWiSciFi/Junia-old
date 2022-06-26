#include "RenderCommand.hpp"

#include <Junia/Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace Junia
{
	// TODO: move to dynamic creation
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}
