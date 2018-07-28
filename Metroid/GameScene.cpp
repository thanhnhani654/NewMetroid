#include "GameScene.h"

void GameScene::Initialize()
{
	test.Initialize();
	test.sprite.get()->SetAnimation("anim_s1_0");
}

void GameScene::UpdateInput(float deltatime)
{
	Camera::getInstance()->UpdateInput(deltatime);
}

void GameScene::Update(float deltatime)
{

}

void GameScene::Draw()
{
	test.Draw();
}