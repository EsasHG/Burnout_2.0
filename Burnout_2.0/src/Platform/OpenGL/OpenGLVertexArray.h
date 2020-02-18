#pragma once

#include "Burnout/Renderer/VertexArray.h"

#include <stdint.h>

namespace Burnout
{
	class OpenGLVertexArray :  public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetAttribPointer(uint32_t index) override;
	private:
		uint32_t m_RendererID;
	};
}

