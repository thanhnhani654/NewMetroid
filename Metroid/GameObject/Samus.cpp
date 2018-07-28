#include "Samus.h"

void Samus::Initialize()
{
	Creature::Initialize();
	sprite.get()->SetAnimation("Walk");
}

void Samus::Ghost_Initialize(){}

void Samus::UpdateInput(float deltatime)
{

}

void Samus::Update(float deltatime)
{

}

void Samus::Draw()
{
	Creature::Draw();
}

void Samus::Destroy()
{}