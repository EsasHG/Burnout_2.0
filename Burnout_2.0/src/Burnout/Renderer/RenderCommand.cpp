
#include "bopch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Burnout
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}