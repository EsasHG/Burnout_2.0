#include "bopch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>

namespace Burnout
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;

		case RendererAPI::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}