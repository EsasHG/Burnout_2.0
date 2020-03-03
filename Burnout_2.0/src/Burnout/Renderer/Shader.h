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

		virtual void UploadMat4Uniform(std::string UniformName, glm::mat4& mat) const = 0;


		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);


	};

}
