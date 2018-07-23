#include "GameScene.h"

void GameScene::Initialize()
{
	test.Initialize();
	test.sprite.get()->SetAnimation("Walk");
}

void GameScene::UpdateInput(float deltatime)
{

}

void GameScene::Update(float deltatime)
{

}

void GameScene::Draw()
{
	test.Draw();
}