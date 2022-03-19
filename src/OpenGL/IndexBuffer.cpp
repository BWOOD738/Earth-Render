#include "IndexBuffer.h"

namespace gl 
{

IndexBuffer::IndexBuffer( GLuint* indices, GLsizeiptr size )
{
	glGenBuffers( 1, &_ib );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ib );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW );
}

IndexBuffer::~IndexBuffer()
{}

void IndexBuffer::Bind()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ib );
}

void IndexBuffer::Unbind()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void IndexBuffer::Delete()
{
	glDeleteBuffers( 1, &_ib );
}

} /* namespace gl */