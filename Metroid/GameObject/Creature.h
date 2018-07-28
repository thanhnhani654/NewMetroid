﻿#pragma once
#include "GameObject.h"
#include "../Component/HPComponent.h"
#include "../Component/MoveComponent.h"


class Creature : public GameObject
{
private:
	MoveComponent moveComponent;
	HPComponent hpComponent;			// Thêm cho nhiều chơi
public:

	#pragma region Inherit

	virtual void Initialize();
	virtual void Ghost_Initialize();				//Initialize mà không lưu lại trong listObject
	virtual void UpdateInput(float deltatime);
	virtual void Update(float deltatime);
	virtual void Draw();
	virtual void Destroy();							//Dùng để xóa những con trỏ bên trong

	#pragma endregion

	#pragma region GetSet

	MoveComponent* GetMoveComponent()
	{
		return &moveComponent;
	}
	
	HPComponent* GetHPComponent()
	{
		return &hpComponent;
	}

	#pragma endregion
};