#pragma once
#include "GameObject.h"
#include "../Component/Box2D.h"

class Tiles : public GameObject
{

private:
	Box2D box;
public:

	#pragma region Inherit

	virtual void Initialize(string tileName);
	virtual void Ghost_Initialize();				//Initialize mà không lưu lại trong listObject
	virtual void UpdateInput(float deltatime);
	virtual void Update(float deltatime);
	virtual void Draw();
	virtual void OnCollision(GameObject* object, float collideTime, int normalX, int normalY);
	virtual void Destroy();							//Dùng để xóa những con trỏ bên trong

	#pragma endregion
};