#include "bopch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Burnout 
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexArray>();
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
