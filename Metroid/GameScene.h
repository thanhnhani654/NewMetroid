#pragma once
#include "GameObject\GameObject.h"
#include "GameObject\Samus.h"
#include "GameObject\Tiles.h"
#include <vector>

class GameScene
{
private:
	Samus samus;
	Tiles tile;
	std::vector<Tiles*> object;
public:

	void Initialize();
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
};