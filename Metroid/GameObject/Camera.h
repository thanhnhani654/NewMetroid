#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#define CameraWidth 400
#define CameraHeight 400

class Camera
{
private:
	D3DXVECTOR2 position;
	static Camera* instance;
	bool bFollowCamera;
public:
	static Camera* getInstance();
	Camera();

	D3DXVECTOR2 GetPosition()
	{
		return position;
	}

	void Update(float deltatime, D3DXVECTOR2 fpos);
};