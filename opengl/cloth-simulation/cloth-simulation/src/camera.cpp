#include "../include/camera.h"

#include"../include/window.h"
#include<GLFW/glfw3.h>

Camera::Camera(Window* _window, glm::vec3 position)
{
    Position = position;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;

	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = SPEED; 
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;

	window = _window;

    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    updateCameraVectors();
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
	if(window->IsKeyDown(GLFW_KEY_W))
        Position += Front * velocity;
	if (window->IsKeyDown(GLFW_KEY_S))
        Position -= Front * velocity;
	if (window->IsKeyDown(GLFW_KEY_A))
        Position -= Right * velocity;
	if (window->IsKeyDown(GLFW_KEY_D))
        Position += Right * velocity;
	if (window->IsKeyDown(GLFW_KEY_SPACE)) {
		Position += Up * velocity;
	}
	if (window->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		Position -= Up * velocity;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, unsigned char constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}