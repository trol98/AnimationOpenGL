#pragma once
#include <cstdint>
#include "OpenGLBufferLayout.h"

class OpenGLVertexBuffer
{
public:
	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(float* vertices, uint32_t size);
   ~OpenGLVertexBuffer();

	void Bind() const;
	void Unbind() const;
	
	void SetData(const void* data, uint32_t size);

	const OpenGLBufferLayout& GetLayout() const  { return m_Layout; }
	void SetLayout(const OpenGLBufferLayout& layout)  { m_Layout = layout; }
private:
	uint32_t m_RendererID;
	OpenGLBufferLayout m_Layout;
};

class OpenGLIndexBuffer 
{
public:
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	~OpenGLIndexBuffer();

	void Bind() const;
	void Unbind() const;

	uint32_t GetCount() const { return m_Count; }
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};
