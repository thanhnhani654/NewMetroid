#pragma once
#include "Creature.h"

class Samus : public Creature
{
public:
	#pragma region Inherit

	void Initialize();
	void Ghost_Initialize();				//Initialize mà không lưu lại trong listObject
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
	void Destroy();							//Dùng để xóa những con trỏ bên trong

	#pragma endregion
};