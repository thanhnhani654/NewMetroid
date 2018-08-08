#pragma once
#include "GameObject.h"
#include "../Component/Box2D.h"

class Item : public GameObject
{
private:
	string _itemName;
public:

	#pragma region GetSet
	bool isHasName(string name);
	#pragma endregion

	virtual void Initialize();
	virtual void Draw();
};