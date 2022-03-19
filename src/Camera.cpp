#include "Camera.h"

Camera::Camera( int width, int height )
: _width( width ), _height( height )
{
}

Camera::~Camera() {}

void Camera::setPosition( vec3 position )
{
    this->_position = position;
}

void Camera::setSpeed( float speed )
{
    this->_speed = speed;
}

void Camera::setSensitivity( float sens )
{
    this->sensitivity = sens;
}

void Camera::Matrix( float FOV, float nearPlane, float farPlane, Shader& shader, std::string uniform )
{   
    /* Have to initialize these or else it will be null */
    mat4 view = mat4( 1.0f );
    mat4 projection = mat4( 1.0f );

    /* Sets correct camera position */
    view = lookAt( _position, _position + orientation, up );
    projection = perspective( radians(FOV), (float)_width / (float)_height, nearPlane, farPlane );

    /* Export all infrormation to the vertex shader*/
    glUniformMatrix4fv( glGetUniformLocation(shader._shaderID, uniform.c_str()), 1, GL_FALSE, value_ptr(projection * view) );
}

            /* No, I will not use a switch
               It's 10pm and I'm lazy
             */

void Camera::HandleInputs( GLFWwindow* window )
{
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
    {
        _position += _speed * orientation;
    }

    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ) 
    {
        _position += _speed * -normalize( cross(orientation, up) );
    }

    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ) 
    {
        _position += _speed * -orientation;
    }

    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
    {
        _position += _speed * normalize( cross(orientation, up) );
    }

    if( glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS )
    {
        _position += _speed * up;
    }

    if( glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS )
    {
        _position += _speed * -up;
    }

    if( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS )
    {
        setSpeed( 0.4f );
    }

    else if( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE )
    {
        setSpeed( _speed );
    }

    /* Handling the mouse inputs */
    if( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS )
    {   
        /* Hide the cursor */
        glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
        
		if ( firstClick )
		{
			glfwSetCursorPos( window, (_width / 2), (_height / 2) );
			firstClick = false;
		}

		/* Stores the coordinates of the cursor */
		double mouseX;
		double mouseY;

		glfwGetCursorPos( window, &mouseX, &mouseY );

		/* Normalize and shift the cordinates */
		float rotX = sensitivity * (float)( mouseY - (_height / 2) ) / _height;
		float rotY = sensitivity * (float)( mouseX - (_width / 2) ) / _width;

		/* Calculates vertical change in the orientation */
		vec3 newOrientation = rotate( orientation, radians(-rotX), normalize(cross(orientation, up)) );

		/* This function makes it so you dont flip the camera around */
		if ( abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f) )
		{
			orientation = newOrientation;
		}

		/* Rotate the orientation left and right */
		orientation = rotate( orientation, radians(-rotY), up );

		/* Sets mouse cursor to the middle of the screen */
		glfwSetCursorPos( window, (_width / 2), (_height / 2) );
	}
	
    else if ( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE )
	{
		/* Unhides cursor */
		glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
		/* Makes sure the next time the camera looks around it doesn't jump */
		firstClick = true;
	}
}
    

