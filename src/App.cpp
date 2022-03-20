#include "App.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void App::Run() 
{
	int width = 1920;
	int height = 1080;

	
	GLfloat vertices[] =
	{ /*    COORDINATES */     /*        COLORS      *//*   TexCoord  */
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	glfwInit();

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	GLFWwindow* window = glfwCreateWindow( width, height, "OpenGL Render", NULL, NULL );

	if ( window == NULL )
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent( window );

	gladLoadGL();
	glViewport( 0, 0, width, height );

	Shader shaderProgram( "shaders/vs.glsl", "shaders/fs.glsl" );


	std::unique_ptr< VertexArray > vao = std::make_unique< VertexArray >();

	vao->Bind();

	VertexBuffer vb( vertices, sizeof(vertices) );

	std::unique_ptr< IndexBuffer > ib = std::make_unique< IndexBuffer >( indices, sizeof( indices ) );
	
	/* Links VBO to VAO */

	/* positions */
	vao->LinkAttrib( vb, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0 );
	/* color */
	vao->LinkAttrib( vb, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	/* texture cordinates */
	vao->LinkAttrib( vb, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)) );

	/* Scale of texture pixels */
	GLuint uniformID = glGetUniformLocation( shaderProgram._shaderID, "scale" );

	/* stbi_set_flip_vertically_on_load( true ); */
	std::unique_ptr< Texture > texture = std::make_unique< Texture >( "DefaultTexture.jpg" );

	vao->Unbind();
	vb.Unbind();
	ib->Unbind();

	glEnable( GL_DEPTH_TEST );
	/* Enable VSYNC */
	glfwSwapInterval( 1 );

	std::unique_ptr< Camera > camera = std::make_unique< Camera >( width, height );
	camera->setPosition( vec3(0.0f, 0.0f, 2.0f) );
	camera->setSpeed( 0.1f );
	camera->setSensitivity( 100.0f );

	while (!glfwWindowShouldClose( window ) )
	{
		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		shaderProgram.Activate();

		camera->HandleInputs( window );

		/* Export matrix data */
		camera->Matrix( 45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix" );

		texture->Bind( 0 );

		vao->Bind();
		glDrawElements( GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers( window );

		glfwPollEvents();
	}

	vao->Delete();
	vb.Delete();
	ib->Delete();
	shaderProgram.Delete();

	glfwDestroyWindow( window );

	glfwTerminate();
}
