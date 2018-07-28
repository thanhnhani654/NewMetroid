#include "GameScene.h"

void GameScene::Initialize()
{
	test.Initialize();
	test.sprite.get()->SetAnimation("Walk");
	test.SetPosition(100, 100);
	samus.Initialize();
	samus.SetPosition(120, 100);
}

void GameScene::UpdateInput(float deltatime)
{

}

void GameScene::Update(float deltatime)
{

}

void GameScene::Draw()
{
	samus.Draw();
	test.Draw();
}