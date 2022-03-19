#pragma once

#include "stb_image.h"

#include <glad/glad.h>
#include <string>
#include <iostream>

namespace gl
{

class Texture
{
public:
	Texture( const std::string& filepath );

    ~Texture();

	void Bind( unsigned int unit );

	void Unbind();

private:
	const std::string& m_filepath;
	GLuint textureID;
};

} /* namespace gl */ 