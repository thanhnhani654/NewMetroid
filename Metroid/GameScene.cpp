#include "GameScene.h"

void GameScene::Initialize()
{
	samus.Initialize();
	samus.SetPosition(100, 100);

	tile.Initialize("Tile_0");
	tile.SetPosition(0, 16);

	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(i * 16+30, 30);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(i * 16 + 30, 200);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(0+30, i*16);
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		Tiles* newObject = new Tiles();
		newObject->Initialize("Tile_0");
		newObject->SetPosition(300+30, i*16);
		object.push_back(newObject);
	}
}

void GameScene::UpdateInput(float deltatime)
{
	samus.UpdateInput(deltatime);
}

void GameScene::Update(float deltatime)
{
	samus.Update(deltatime);
}

void GameScene::Draw()
{
	samus.Draw();
	tile.Draw();
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Draw();
	}
}