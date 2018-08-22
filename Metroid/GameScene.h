#pragma once
#include "GameObject\GameObject.h"
#include "GameObject\Samus.h"
#include "GameObject\Tiles.h"
#include "GameObject\Camera.h"
#include "GameObject\Bullet.h"
#include "GameObject\Item.h"
#include "GameObject\Zoomer.h"
#include "GameObject\Reo.h"
#include <fstream>
#include <vector>
using namespace std;

class GameScene
{
private:
	Samus samus;
	

	Item item;
	std::vector<Tiles*> object;

	Zoomer zoomer;
	Reo reo;
public:

	void Initialize();
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();


	// Tạm thời. Sau này có QuadTree sẽ xóa
	void MapLoader();
};