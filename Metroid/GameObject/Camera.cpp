#include "Camera.h"

Camera* Camera::instance;

Camera* Camera::getInstance()
{
	if (instance == nullptr)
		instance = new Camera();
	return instance;
}

Camera::Camera()
{
	bFollowCamera = true;
	position.x = 0;
	position.y = 0;
}

void Camera::Update(float deltatime, D3DXVECTOR2 fpos)
{
	if (bFollowCamera)
	{
		position.x = fpos.x - CameraWidth / 2;
		position.y = fpos.y - CameraHeight / 2;
		//std::cout << "X: " << position.x << "\tY: " << position.y << std::endl;
	}
}