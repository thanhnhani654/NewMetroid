#include "GameScene.h"

void GameScene::Initialize()
{
	samus.Initialize();
	samus.SetPosition(100, 100);

	for (int i = 0; i < 20; i++)
	{
		GameObject* newObject = new GameObject();
		newObject->Initialize();
		newObject->SetPosition(i * 16, 30);
		newObject->sprite.get()->SetAnimation("Tile_0");
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		GameObject* newObject = new GameObject();
		newObject->Initialize();
		newObject->SetPosition(0, i*16);
		newObject->sprite.get()->SetAnimation("Tile_0");
		object.push_back(newObject);
	}
	for (int i = 0; i < 20; i++)
	{
		GameObject* newObject = new GameObject();
		newObject->Initialize();
		newObject->SetPosition(300, i*16);
		newObject->sprite.get()->SetAnimation("Tile_0");
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
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Draw();
	}
}