#include "splpch.h"
#include "Texture.h"

#include "Spotlight/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Spotlight
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, bool isRGBA)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:     SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:   return CreateRef<OpenGLTexture2D>(width, height, isRGBA);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;	
	}

	Ref<Texture2D> Texture2D::Create(const std::string &filepath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:     SPL_CORE_ASSERT(false, "RendererAPI::None is currently selected!"); return nullptr;
			case RendererAPI::API::OpenGL:   return CreateRef<OpenGLTexture2D>(filepath);
		}

		SPL_CORE_ASSERT(false, "Unknown value. No Renderer API is selected!");
		return nullptr;	
	}

}