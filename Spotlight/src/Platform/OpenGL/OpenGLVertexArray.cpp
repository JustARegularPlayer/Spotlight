#include "splpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Spotlight
{

	OpenGLVertexArray::OpenGLVertexArray()
		: m_ArrayID(0)
	{
		glGenVertexArrays(1, &m_ArrayID);
		glBindVertexArray(m_ArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}