#include "splpch.h"
#include "VertexArray.h"

#include "Spotlight/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spotlight
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::None:		SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;
	}

}