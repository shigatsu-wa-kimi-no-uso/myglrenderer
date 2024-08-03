#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "common/global.h"

struct CameraConfig
{
	float yaw;
	float pitch;

	float height;
	float width;
	float fov;
	float near;
	float far;

	vec3 cameraPos;
	vec3 worldUp;
	union {
		vec3 front;
		vec3 negZAxis;
	};
};

enum class CameraMovement
{
	FORWARD = 1 ,
	BACKWORD = 2,
	LEFT = 4,
	RIGHT = 8,
	UP = 16,
	DOWN = 32
};


class Camera
{
private:
	mat4 projection;
	mat4 view;
public:
	struct _Config: CameraConfig {

	
		union {
			vec3 right;
			vec3 xAxis;
		};
		union {
			vec3 cameraUp;
			vec3 yAxis;
		};
		_Config();
		_Config(const CameraConfig& config);
	} config;

public:
	Camera();

	Camera(const CameraConfig& config);

	void setCameraConfig(const CameraConfig& config);

	void setLookingCenter(const vec3& center);

	void updateProjection();

	void updateView();

	vec3 getPosition();

	const mat4& getView() const;

	const mat4& getProjection() const;

	float getFoV() const;

	const void* getViewPtr() const;

	const void* getProjectionPtr() const;

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void updateCameraPos(const uint& movement, float deltaVec);

	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void updateCameraView(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void updateCameraZoom(float yoffset);

	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraAxes();

};

#endif // !CAMERA_H

