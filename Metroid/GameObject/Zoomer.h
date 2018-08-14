#pragma once
#include "Creature.h"


enum eZoomerState
{
	OnZState,
	UnderZState,
	LeftZState,
	RightZState
};

class Zoomer : public Creature
{
private:

	bool bGoRight;
	eZoomerState state;
	bool bChangeState;
	bool bChangeStateOnOutCollision;
	float speed;
	D3DXVECTOR2 prevPosition;

	//Method
	void ChangeState();
	void SetGravity();
	void AiMove();

public:

	#pragma region GetSet
	void GoRight()
	{
		bGoRight = true;
	}
	void GoLeft()
	{
		bGoRight = false;
	}

	void SetState(eZoomerState state)
	{
		this->state = state;
	}

	eZoomerState GetState()
	{
		return state;
	}

	#pragma endregion

	//Inherit From Creature
	void Initialize();
	void Update(float deltatime);
	void Draw();
	void OnCollision(GameObject* object, float collideTime, int normalX, int normalY);
	void Destroy();							//Dùng để xóa những con trỏ bên trong
};