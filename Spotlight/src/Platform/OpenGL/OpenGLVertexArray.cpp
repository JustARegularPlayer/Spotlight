#include "splpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Spotlight
{

	static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Bool:   return GL_BOOL;
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Byte:   return GL_BYTE;
			case ShaderDataType::Byte2:  return GL_BYTE;
			case ShaderDataType::Byte3:  return GL_BYTE;
			case ShaderDataType::Byte4:  return GL_BYTE;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
		}
		SPL_CORE_ASSERT(false, "Specified ShaderDataType unknown!");
		return 0;
	}

	// VERTEX ARRAY ================================================================

	OpenGLVertexArray::OpenGLVertexArray()
		: m_ArrayID(0), m_VertexBuffers(0), m_IBO(nullptr)
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

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vbo)
	{
		glBindVertexArray(m_ArrayID);
		vbo->Bind();

		uint16_t i = 0;
		const auto &layout = vbo->GetLayout();

		SPL_CORE_ASSERT(layout.GetAllElements().size(), "Vertex buffer has no layout!");

		for (const auto &element : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				element.GetComponentCount(),
				ShaderDataTypeToGLenum(element.Type),
				element.Normalized,
				layout.GetStride(),
				(const void *) element.Offset);
			i++;
		}
		m_VertexBuffers.push_back(vbo);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &ibo)
	{
		glBindVertexArray(m_ArrayID);
		ibo->Bind();

		m_IBO = ibo;
	}

}