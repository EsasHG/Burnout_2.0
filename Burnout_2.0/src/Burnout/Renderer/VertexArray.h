#pragma once

namespace Burnout
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetAttribPointer(uint32_t index) = 0;

		static VertexArray* Create();
	};
}

