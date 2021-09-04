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

		virtual void AddVertexBuffer(const Ref<VertexBuffer> &vbo) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> &ibo) override;

		virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer> &GetIndexBuffer() const override { return m_IBO; }
	private:
		uint32_t m_ArrayID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IBO;
	};

}