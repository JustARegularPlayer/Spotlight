#include "splpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Spotlight
{

	// VERTEX BUFFER =================================================================

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_BufferID(0)
	{
		SPL_PROFILE_FUNC();

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		SPL_PROFILE_FUNC();

		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		SPL_PROFILE_FUNC();

		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		SPL_PROFILE_FUNC();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// INDEX BUFFER ==================================================================

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_BufferID(0), m_Count(count)
	{
		SPL_PROFILE_FUNC();

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		SPL_PROFILE_FUNC();

		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		SPL_PROFILE_FUNC();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		SPL_PROFILE_FUNC();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}