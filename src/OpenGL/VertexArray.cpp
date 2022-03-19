#include "VertexArray.h"

namespace gl
{

VertexArray::VertexArray()
{
	glGenVertexArrays( 1, &ID );
}

VertexArray::~VertexArray() { }

void VertexArray::LinkAttrib(VertexBuffer v, GLuint layout, GLuint nComponets, GLenum type, GLsizeiptr stride, void* offset)
{
	v.Bind();
	glVertexAttribPointer( layout, nComponets, type, GL_FALSE, stride, offset );
	glEnableVertexAttribArray( layout );
	v.Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray( ID );
}

void VertexArray::Unbind()
{
	glBindVertexArray( 0 );
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &ID);
}


} /* namespace gl */