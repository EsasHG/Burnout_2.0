#pragma once

#include <string>
#include <glm/mat4x4.hpp>
namespace Burnout
{

	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadMat4Uniform(const std::string& UniformName, const glm::mat4& mat) const = 0;


		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);


	};

}
