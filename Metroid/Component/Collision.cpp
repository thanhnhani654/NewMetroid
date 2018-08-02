#include "Collision.h"

Collision* Collision::instance;

Collision* Collision::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Collision();
	}
	return instance;
}

bool Collision::IsIntersection(Box object1, Box object2)
{
	if (object1.position.x							< object2.position.x + object2.size.x		&&
		object1.position.x + object1.size.x			> object2.position.x					&&
		object1.position.y							< object2.position.y + object2.size.y		&&
		object1.position.y + object1.size.y			> object2.position.y
		)
		return true;
	return false;
}

Box Collision::GetBroadphaseBox(Box2D &object, float delta)
{
	Box temp;
	temp.position.x = object.GetVelocity().x == 0 ? object.GetBox().position.x : object.GetBox().position.x + object.GetVelocity().x * delta;
	temp.position.y = object.GetVelocity().y == 0 ? object.GetBox().position.y : object.GetBox().position.y + object.GetVelocity().y * delta;
	temp.size.x = object.GetBox().size.x;
	temp.size.y = object.GetBox().size.y;

	return temp;
}

float Collision::Distance(Box object1, Box object2)
{
	D3DXVECTOR2 point1;
	D3DXVECTOR2 point2;
	point1.x = object1.position.x + object1.size.x / 2;
	point1.y = object1.position.y + object1.size.y / 2;
	point2.x = object2.position.x + object2.size.x / 2;
	point2.y = object2.position.y + object2.size.y / 2;
	
	return sqrt((point2.x - point1.x)*(point2.x - point1.x) + (point2.y - point1.y)*(point2.y - point1.y));
}

void Collision::AddCheckListBox(Box2D &object, float dist)
{
	CheckBox checkBox;
	checkBox.box = object;
	checkBox.dist = dist;
	if (_CheckListBox.size() == 0)
	{
		_CheckListBox.push_back(checkBox);
		return;
	}
	for (int i = 0; i < _CheckListBox.size(); i++)
	{
		if (dist < _CheckListBox[i].dist)
		{
			_CheckListBox.insert(_CheckListBox.begin() + i, checkBox);
			return;
		}
	}
	_CheckListBox.insert(_CheckListBox.end() + 1, checkBox);
}

void Collision::doCollision(Box2D object)
{
	if (_CheckListBox.size() == 0)
		return;

	for (int i = 0; i < _CheckListBox.size(); i++)
	{
		object.getGameObject()->OnCollision(_CheckListBox[i].box.getGameObject());
	}

	_CheckListBox.clear();
}

void Collision::CollisionChecker(float deltatime)
{
	for (int i = 0; i < Box2D::listBox.size(); i++)
	{
		// Next nếu Box được lấy đã bị disable hoặc nó thuộc loại Static vì Static không di chuyển nên không cần xét nó với Box khác,
		// chỉ cần xét vật di chuyển với nó là được
		if (!Box2D::listBox[i].get().isEnable() || Box2D::listBox[i].get().GetType() == eBoxType::Static)
			continue;

		// Xét Box thứ 2
		for (int ii = 0; ii < Box2D::listBox.size(); ii++)
		{
			// Nếu Box thứ 2 đã bị disable hoặc trùng với Box1 thì next
			if (!Box2D::listBox[ii].get().isEnable() || &Box2D::listBox[ii].get() == &Box2D::listBox[i].get())
				continue;

			// Kiem tra neu co the xay ra va cham trong tuong lai
			// thi se dua vao danh sach cai box can xet
			if (!IsIntersection(GetBroadphaseBox(Box2D::listBox[ii].get(), deltatime), GetBroadphaseBox(Box2D::listBox[i].get(), deltatime)))
				continue;

			AddCheckListBox(Box2D::listBox[ii].get(), Distance(Box2D::listBox[i].get().GetBox(), Box2D::listBox[ii].get().GetBox()));

			// Thuc hien va cham 
			doCollision(Box2D::listBox[ii].get());
		}
	}
}

float Collision::CollisionDetection(Box2D object1, Box2D object2, int* normalx, int* normaly, float deltatime)
{
	D3DXVECTOR2 vec1 = object1.GetVelocity();
	D3DXVECTOR2 vec2 = object2.GetVelocity();
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	Box box1 = object1.GetBox();
	Box box2 = object2.GetBox();


	float dxEntry, dxExit;
	float dyEntry, dyExit;

	float txEntry, tyEntry, tEntry;
	float txExit, tyExit, tExit;

	if (vec1.x > 0)
	{
		dxEntry = box2.position.x - (box1.position.x + box1.size.x);
		dxExit = (box2.position.x + box2.size.x) - box1.position.x;
	}
	else
	{
		dxEntry = (box2.position.x + box2.size.x) - box1.position.x;
		dxExit = box2.position.x - (box1.position.x + box1.size.x);
	}

	if (vec1.y > 0)
	{
		dyEntry = box2.position.y - (box1.position.y + box1.size.y);
		dyExit = (box2.position.y + box2.size.y) - box1.position.y;
	}
	else
	{
		dyEntry = (box2.position.y + box2.size.y) - box1.position.y;
		dyExit = box2.position.y - (box1.position.y + box1.size.y);
	}

	if (vec1.x == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / vec1.x;
		txExit = dxExit / vec1.x;
	}

	if (vec1.y == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / vec1.y;
		tyExit = dyExit / vec1.y;
	}

	tEntry = max(txEntry, tyEntry);
	tExit = min(txExit, tyExit);
	tEntry *= deltatime;
	tExit *= deltatime;

	if (tEntry			>			tExit ||
		txEntry < 0.0f && tyEntry < 0.0f ||
		txEntry > deltatime && tyEntry > deltatime)
		return deltatime;

	if (txEntry > tyEntry)
	{
		*normalx = dxEntry > 0.0f ? 1 : -1;
	}
	else
	{
		*normaly = dyEntry > 0.0f ? 1 : -1;
	}

	return tEntry;
}