#include "Creature.h"

void Creature::Initialize()
{
	GameObject::Initialize();
	moveComponent.Initialize(GetPosition_Ptr(), GetVelocity_Ptr());
}

void Creature::Ghost_Initialize()
{

}

void Creature::UpdateInput(float deltatime)
{}

void Creature::Update(float deltatime)
{}

void Creature::Draw()
{
	GameObject::Draw();
}

void Creature::Destroy()
{}