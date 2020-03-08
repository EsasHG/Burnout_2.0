#pragma once

#include "Burnout/Renderer/Shader.h"

namespace Burnout 
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void UploadMat4Uniform(const std::string& UniformName, const glm::mat4& mat) const override;

	private:
		uint32_t m_RendererID;
	
	};
}

