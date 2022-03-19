#pragma once

#include <glad/glad.h>

namespace gl 
{

class VertexBuffer
{
public:
	VertexBuffer( GLfloat* vertices, GLsizeiptr size );
	VertexBuffer( const VertexBuffer& other ) = default;

    ~VertexBuffer();

	void Bind();

	void Unbind();
	
	void Delete();

private:
	GLuint _vbo;
};

} /* namespace gl */