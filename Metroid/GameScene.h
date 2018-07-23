#pragma once
#include "GameObject\GameObject.h"

class GameScene
{
private:
	GameObject test;
public:

	void Initialize();
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
};