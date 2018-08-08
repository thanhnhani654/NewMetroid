#include "Item.h"

bool Item::isHasName(string name)
{
	if (name == _itemName)
		return true;
	return false;
}

void Item::Initialize()
{
	GameObject::Initialize();
	GetTagMethod()->AddTag(eTag::ItemTag);
}

void Item::Draw()
{
	GameObject::Draw();
}