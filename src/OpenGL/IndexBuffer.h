#pragma once

namespace gl
{

#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer( GLuint* indices, GLsizeiptr size );
	IndexBuffer( const IndexBuffer& other ) = delete;

	~IndexBuffer();
	
	void Bind();

	void Unbind();

	void Delete();

private:
	GLuint _ib;
};

} /* namespace gl */