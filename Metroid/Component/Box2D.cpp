#include "Box2D.h"

std::vector<reference_wrapper<Box2D>> Box2D::listBox;

void Box2D::DynamicInitialize(GameObject* object, float width, float height)
{
	gameObject = object;
	gameObject->GetPosition_Ref(box.position);
	box.size.x = width;
	box.size.y = height;
	deleted = false;
	bEnable = true;
	type = eBoxType::Dynamic;
}

void Box2D::StaticInitialize(GameObject* object, float width, float height)
{
	gameObject = object;
	gameObject->GetPosition_Ref(box.position);
	box.size.x = width;
	box.size.y = height;
	deleted = false;
	bEnable = true;
	type = eBoxType::Static;
}