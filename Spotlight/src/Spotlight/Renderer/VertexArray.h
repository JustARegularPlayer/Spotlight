#pragma once

#include "Spotlight/Renderer/Buffer.h"

namespace Spotlight
{

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

		static VertexArray *Create();
	};

}