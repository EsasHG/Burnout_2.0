#include "bopch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glad/glad.h>

namespace Burnout
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;

		case RendererAPI::API::OpenGL:	return new OpenGLShader(filepath);
		default:
			break;
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;

		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}