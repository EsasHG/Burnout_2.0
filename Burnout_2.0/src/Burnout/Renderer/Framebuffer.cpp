#include "bopch.h"
#include "Framebuffer.h"

#include "Burnout/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Burnout
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		BO_CORE_ASSERT(false, " RendererAPI::None: is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);
		}
		BO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
