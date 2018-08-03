#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../GameObject/GameObject.h"
#include <vector>

struct Box
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;			//x = width, y = height
};

enum eBoxType {Dynamic, Static};

class Box2D
{
private:
	/*D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;*/

	GameObject *gameObject;
	Box box;
	bool deleted;
	bool bEnable;
	eBoxType type;

	
public:
	static std::vector<reference_wrapper<Box2D>> listBox;

	#pragma region GetSet
	GameObject* getGameObject()
	{
		return gameObject;
	}

	Box GetBox()
	{
		return box;
	}

	void SetBox(float &x, float &y, float w, float h)
	{
		box.position.x = x;
		box.position.y = y;
		box.size.x = w;
		box.size.y = h;
	}

	void SetPosition()
	{
		box.position.x = gameObject->GetPosition().x - box.size.x / 2;
		box.position.y = gameObject->GetPosition().y - box.size.y / 2;
	}

	void SetSize(float width, float height)
	{
		box.size.x = width;
		box.size.y = height;
	}

	D3DXVECTOR2 GetPosition()
	{
		return gameObject->GetPosition();
	}

	D3DXVECTOR2 GetVelocity()
	{
		return gameObject->GetVelocity();
	}

	D3DXVECTOR2 GetSize()
	{
		return box.size;
	}

	void SetDeleted()
	{
		deleted = true;
	}

	bool IsDeleted()
	{
		return deleted;
	}

	void Enable()
	{
		bEnable = true;
	}

	void Disable()
	{
		bEnable = false;
	}

	bool isEnable()
	{
		return bEnable;
	}

	void SetStaticType()
	{
		type = eBoxType::Static;
	}

	void SetDynamicType()
	{
		type - eBoxType::Dynamic;
	}

	eBoxType GetType()
	{
		return type;
	}

#pragma endregion

	void DynamicInitialize(GameObject* object, float width, float height);
	void StaticInitialize(GameObject* object, float width, float height);
};