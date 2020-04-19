#include "bopch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Burnout
{

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;

			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;

			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, size);
			default:
				break;
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}


