#include "splpch.h"
#include "Buffer.h"

#include "Spotlight/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Spotlight
{

	// VERTEX BUFFER =================================================================

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

	// INDEX BUFFER ==================================================================

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:    SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}
}