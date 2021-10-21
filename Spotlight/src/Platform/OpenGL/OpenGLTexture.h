#pragma once

#include "Spotlight/Renderer/Texture.h"

typedef unsigned int GLenum;

namespace Spotlight
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, bool isRGBA = true);
		OpenGLTexture2D(const std::string &filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void *data, uint32_t size) override;

		virtual void Bind(uint32_t slot) const override;

		virtual bool operator==(const Texture &other) const override
		{
			return m_TextureID == ((OpenGLTexture2D &)other).m_TextureID;
		}
	private:
		std::string m_Filepath;
		uint32_t m_Width, m_Height;
		uint32_t m_TextureID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}