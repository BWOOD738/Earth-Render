#pragma once

#include "VertexBuffer.h"

namespace gl
{

class VertexArray
{
public:
	VertexArray();

    ~VertexArray();

	void LinkAttrib( VertexBuffer v, GLuint layout, GLuint nComponets, GLenum type, GLsizeiptr stride, void* offset );

	void Bind();

	void Unbind();

	void Delete();

private:
	GLuint ID;
};

} /* namespace gl */