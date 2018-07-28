#pragma once
#include "GameObject\GameObject.h"
#include "GameObject\Samus.h"

class GameScene
{
private:
	GameObject test;
	Samus samus;
public:

	void Initialize();
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
};