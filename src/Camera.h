#pragma once 

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <string>

#include "OpenGL/Shader.h"

/* gl math*/
using namespace glm;
/* namespace in OpenGL directory */
using namespace gl;

class Camera
{
public:
    /*******************************************************
    CONSTRUCTOR - Width and height will be the same as the 
    window height in App.cpp
    *******************************************************/
    Camera( int width, int height );
    ~Camera();

    /* getters and setters */
    void setPosition( vec3 position );

    /* Set camera speed in meters per second */
    void setSpeed( float speed );

    void setSensitivity( float sens );

    /* Updates the camera maxtrix information to the Vertex shader*/
    void Matrix( float FOV, float nearPlane, float farPlane, Shader& shader, std::string uniform );

    void HandleInputs( GLFWwindow* window );

private:
    vec3 _position;
    vec3 orientation = vec3( 0.0f, 0.0f, -1.0f );
    vec3 up = vec3( 0.0f, 1.0f, 0.0f );

    float _speed;
    float sensitivity;

    /* Stores the height and width of the window */
    int _width;
    int _height;

     /* Prevents the jankyness of the camera jumping around all the time */
    bool firstClick = true;
};