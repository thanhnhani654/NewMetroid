#include "MoveComponent.h"

void MoveComponent::Initialize(D3DXVECTOR2* position, D3DXVECTOR2* velocity)
{
	this->position = position;
	this->velocity = velocity;
	speed = 5;
	limitedSpeed = 1000;
	bGravity = false;
	gravity = 10;
}

void MoveComponent::MoveUp()
{
	if (!bGravity)
		velocity->y = speed;
}

void MoveComponent::MoveDown()
{
	if (!bGravity)
		velocity->y = speed;
}

void MoveComponent::Jump()
{
	if (!bGravity)
		return;
	velocity->y = jumpPower;
}

void MoveComponent::MoveLeft()
{
	velocity->x = -speed;
}

void MoveComponent::MoveRight()
{
	velocity->x = speed;
}

void MoveComponent::IdleX()
{
	velocity->x = 0;
}

void MoveComponent::IdleY()
{
	if (!bGravity)
		velocity->y = 0;
	else
	{
		if (abs((int)velocity->y) < limitedSpeed)
			velocity->y -= gravity;
		else
		{
			if (velocity->y < 0)
				velocity->y = limitedSpeed;
		}
	}
}

void MoveComponent::TinhVanTocDuaTrenPhuongTrinhTheoThoiGian(float ptx, float pty)
{
	//Tin Nguoi VKL!!!
	velocity->x = ptx;
	velocity->y = pty;
}

void MoveComponent::UpdateMovement(float deltatime)
{
	position->x += velocity->x * deltatime;
	position->y += velocity->y * deltatime;
}