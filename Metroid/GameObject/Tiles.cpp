#include "Tiles.h"

void Tiles::Initialize(string tileName)
{
	GameObject::Initialize();
	sprite.get()->SetAnimation(tileName);
	box.StaticInitialize(this, 16, 16);
	box.SetPivot(8, 8);
	GetTagMethod()->AddTag(eTag::TilesTag);
}

void Tiles::Ghost_Initialize()
{

}

void Tiles::UpdateInput(float deltatime)
{}

void Tiles::Update(float deltatime)
{}

void Tiles::Draw()
{
	GameObject::Draw();
}

void Tiles::OnCollision(GameObject* object, float collideTime, int normalX, int normalY)
{

}

void Tiles::Destroy()
{}