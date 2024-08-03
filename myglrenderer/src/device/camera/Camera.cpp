#include "Camera.h"

Camera::Camera() {}

Camera::Camera(const CameraConfig& config) :config(config) {}


Camera::_Config::_Config() {}

Camera::_Config::_Config(const CameraConfig& config) :CameraConfig(config) {}

void Camera::setCameraConfig(const CameraConfig& config)
{
	this->config = config;
	updateCameraAxes();
	updateView();
	updateProjection();
}

void Camera::setLookingCenter(const vec3& center)
{
	config.front = normalize( center - config.cameraPos);
}

void Camera::updateProjection()
{
	projection = perspective(radians(config.fov), config.width / config.height, config.near, config.far);
}

void Camera::updateView()
{
	view = lookAt(config.cameraPos, config.cameraPos + config.front, config.cameraUp);
}

vec3 Camera::getPosition() {
	return config.cameraPos;
}

const mat4& Camera::getView() const
{
	return view;
}

const mat4& Camera::getProjection() const
{
	return projection;
}

float Camera::getFoV() const {
	return config.fov;
}

const void* Camera::getViewPtr() const {
	return glm::value_ptr(view);
}

const void* Camera::getProjectionPtr() const {
	return glm::value_ptr(projection);
}


// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::updateCameraPos(const uint& movement, float deltaVec) {
	vec3 direction = vec3(0, 0, 0);
	if (movement & uint(CameraMovement::FORWARD)) {
		direction += config.front;
	}
	if (movement & uint(CameraMovement::BACKWORD)) {
		direction -= config.front;
	}
	if (movement & uint(CameraMovement::LEFT)) {
		direction -= config.right;
	}
	if (movement & uint(CameraMovement::RIGHT)) {
		direction += config.right;
	}
	if (movement & uint(CameraMovement::UP)) {
		direction += config.cameraUp;
	}
	if (movement & uint(CameraMovement::DOWN)) {
		direction -= config.cameraUp;
	}

	config.cameraPos += direction * deltaVec;
	updateView();
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::updateCameraView(float xoffset, float yoffset, GLboolean constrainPitch) {
	config.yaw += xoffset;
	config.pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (config.pitch > 89.0f) {
			config.pitch = 89.0f;
		}
		if (config.pitch < -89.0f) {
			config.pitch = -89.0f;
		}
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraAxes();
	updateView();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::updateCameraZoom(float yoffset)
{
	config.fov -= yoffset;
	if (config.fov < 1.0f) {
		config.fov = 1.0f;
	}

	if (config.fov > 75.0f) {
		config.fov = 75.0f;
	}

	updateProjection();
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraAxes()
{
	// calculate the new Front vector
	vec3 front;
	front.x = cos(radians(config.yaw)) * cos(radians(config.pitch));
	front.y = sin(radians(config.pitch));
	front.z = sin(radians(config.yaw)) * cos(radians(config.pitch));
	config.front = normalize(front);

	// also re-calculate the Right and Up vector
	config.right = normalize(cross(config.front, config.worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	config.cameraUp = normalize(cross(config.right, config.front));
}
