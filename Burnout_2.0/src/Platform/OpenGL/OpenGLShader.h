#pragma once

#include "Burnout/Renderer/Shader.h"

#include <string>
#include <glm/mat4x4.hpp>

namespace Burnout 
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		void UploadUniformInt(const std::string& UniformName, int value) const;

		void UploadUniformFloat(const std::string& UniformName, float value) const;
		void UploadUniformFloat2(const std::string& UniformName, const glm::vec2& values) const;
		void UploadUniformFloat3(const std::string& UniformName, const glm::vec3& values) const;
		void UploadUniformFloat4(const std::string& UniformName, const glm::vec4& values) const;

		void UploadUniformMat3(const std::string& UniformName, const glm::mat3& mat) const;
		void UploadUniformMat4(const std::string& UniformName, const glm::mat4& mat) const;



	private:
		uint32_t m_RendererID;
	};
}

