#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../Controllable.h"

class Camera : public Controllable
{
public:
	D3DXVECTOR2 position;
	float speed;

	static Camera* inst;

	static Camera* getInstance()
	{
		if (inst == nullptr)
			inst = new Camera();
		return inst;
	}

	Camera()
	{
		position.x = 0;
		position.y = 0;
		speed = 5;
	}


	void UpdateInput(float deltatime)
	{
		_ProcessKeyBoard();

		if (IsKeyDown(DIK_W))
			position.y += speed;
		if (IsKeyDown(DIK_S))
			position.y -= speed;
		if (IsKeyDown(DIK_D))
			position.x += speed;
		if (IsKeyDown(DIK_A))
			position.x -= speed;
		
	}
};