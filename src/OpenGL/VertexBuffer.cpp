#include "VertexBuffer.h"

namespace gl
{

VertexBuffer::VertexBuffer( GLfloat* vertices, GLsizeiptr size )
{
	glGenBuffers( 1, &_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
	glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
}

VertexBuffer::~VertexBuffer() { }

void VertexBuffer::Bind() 
{
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
}

void VertexBuffer::Unbind()
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void VertexBuffer::Delete()
{
	glDeleteBuffers( 1, &_vbo );
}

} /* namespace gl */