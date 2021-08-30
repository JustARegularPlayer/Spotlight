#pragma once

#include "Spotlight/Renderer/VertexArray.h"

namespace Spotlight
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vbo) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &ibo) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override { return m_IBO; }
	private:
		uint32_t m_ArrayID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IBO;
	};

}