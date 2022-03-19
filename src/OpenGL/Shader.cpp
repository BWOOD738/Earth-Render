#include "Shader.h"

namespace gl 
{

std::string GetShaderFile( std::string filename )
{
	std::ifstream in( filename, std::ios::binary );
	if( in )
	{
		std::string contents;
		in.seekg( 0, std::ios::end );
		contents.resize( in.tellg() );
		in.seekg( 0, std::ios::beg );

		in.read( &contents[0], contents.size() );
		in.close();
		return( contents );
	}
	throw( errno );
}

Shader::Shader( const char* vertexFile, const char* fragFile )
{
	std::string vertexCode = GetShaderFile( vertexFile );
	std::string fragmentCode = GetShaderFile( fragFile );

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	
	glShaderSource( vertexShader, 1, &vertexSource, NULL );

	glCompileShader( vertexShader );
	
	GetShaderCompileErrors( vertexShader, "VERTEX" );

	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
	
	glCompileShader( fragmentShader );

	_shaderID = glCreateProgram();

	glAttachShader( _shaderID, vertexShader );
	glAttachShader( _shaderID, fragmentShader );

	glLinkProgram ( _shaderID );

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
}

Shader::~Shader() { }

void Shader::Activate()
{
    glUseProgram( _shaderID );
}

void Shader::Delete()
{
    glDeleteProgram( _shaderID );
}

void Shader::GetShaderCompileErrors( GLuint shader, std::string type )
{
	GLint hasCompiled;

	char infoLog[512];

	if ( type != "PROGRAM" )
	{
		glGetShaderiv( shader, GL_COMPILE_STATUS, &hasCompiled );
		
		if ( hasCompiled == GL_FALSE )
		{
			glGetShaderInfoLog( shader, 512, NULL, infoLog );
			std::cout << "Shader Compilation Error for: " << type << "\n" << std::endl;
		}
	}

	else
	{
		glGetProgramiv( shader, GL_LINK_STATUS, &hasCompiled );
		if( hasCompiled == GL_FALSE )
		{
			glGetProgramInfoLog( shader, 1024, NULL, infoLog );
			std::cout << "Shader Linking Error for: " << type << "\n" << infoLog << std::endl;
		}
	}
}

} /* namespace gl */