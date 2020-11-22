#pragma once

#include <glad/glad.h>
#include <string>

class OpenGLTexture2D
{
public:
	OpenGLTexture2D(uint32_t width, uint32_t height);
	OpenGLTexture2D(const std::string& path);
	~OpenGLTexture2D();

	uint32_t GetWidth() const { return m_Width;  }
	uint32_t GetHeight() const  { return m_Height; }
	uint32_t GetRendererID() const  { return m_RendererID; }
	
	void SetData(void* data, uint32_t size);

	void Bind(uint32_t slot = 0) const;

private:
	std::string m_Path;
	uint32_t m_Width, m_Height;
	uint32_t m_RendererID;
	GLenum m_InternalFormat, m_DataFormat;
};


