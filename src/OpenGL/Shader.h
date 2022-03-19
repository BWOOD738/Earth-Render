#pragma once

/* Standard headers */
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <glad/glad.h>

namespace gl 
{

std::string GetShaderFile( std::string filename );

class Shader
{
public:
	Shader( const char* vertexFile, const char* fragFile );

	~Shader();

	void Activate();
	void Delete();

	void GetShaderCompileErrors( GLuint shader, std::string type );
	
	/* This needs to be public */
	GLuint _shaderID;
};

} /* namespace gl */