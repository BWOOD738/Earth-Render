#include "Texture.h"

namespace gl 
{

Texture::Texture( const std::string& filepath ) 
	: m_filepath( filepath )
{
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID ); 
	/* the texture wrapping parameters */
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST_MIPMAP_LINEAR );	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST );
	/*texture filtering parameters*/
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT );
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load( filepath.c_str() , &width, &height, &nrChannels, 0 );
	
	if ( data )
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free( data );
}

Texture::~Texture()
{
	glDeleteTextures( 1, &textureID );
}

void Texture::Bind( unsigned int unit )
{
	glBindTexture( GL_TEXTURE_2D, textureID + unit );
}

void Texture::Unbind()
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}

} /* namespace gl */