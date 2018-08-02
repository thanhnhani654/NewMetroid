#pragma once
#include "GameObject\GameObject.h"
#include "GameObject\Samus.h"
#include <vector>

class GameScene
{
private:
	Samus samus;
	std::vector<GameObject*> object;
public:

	void Initialize();
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
};