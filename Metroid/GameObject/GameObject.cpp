#include "GameObject.h"

// Khai báo các biến toàn cục
#pragma region Define
std::vector<GameObject*> GameObject::listObject;
#pragma endregion

void GameObject::Initialize()
{
	listObject.push_back(this);
}

void GameObject::Ghost_Initialize()
{

}

void GameObject::UpdateInput(float deltatime)
{

}

void GameObject::Update(float deltatime)
{

}

void GameObject::Draw()
{

}

void GameObject::Destroy()
{

}

void GameObject::DestroyProcess()
{
	int mark = -1;
	std::vector<GameObject*>::iterator it;
	for (it = listObject.begin(); it != listObject.end(); it++)
	{
		if ((*it)->deleted)
		{
			(*it)->Destroy();
			break;
		}
	}
	if (mark != (-1))
	{
		listObject.erase(it);
		DestroyProcess();
	}
}