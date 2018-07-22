#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class GameObject
{
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	bool deleted;

public:
	static std::vector<GameObject*> listObject;
	std::vector<GameObject*> childObject;

	#pragma region GetSet
	D3DXVECTOR2 GetPosition()
	{
		return position;
	}

	D3DXVECTOR2* GetPtrPosition()
	{
		return &position;
	}

	void SetPosition(D3DXVECTOR2 pos)
	{
		position = pos;
	}

	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	D3DXVECTOR2 GetVelocity()
	{
		return velocity;
	}

	D3DXVECTOR2* GetPtrVelocity()
	{
		return &velocity;
	}

	void SetVelocity(D3DXVECTOR2 vec)
	{
		velocity = vec;
	}

	void SetVelocity(float x, float y)
	{
		velocity.x = x;
		velocity.y = y;
	}

	bool isDeleted()
	{
		return deleted;
	}

	void SetDeleted()
	{
		deleted = true;
	}
	#pragma endregion

	virtual void Initialize();
	virtual void Ghost_Initialize();				//Initialize mà không lưu lại trong listObject
	virtual void UpdateInput(float deltatime);
	virtual void Update(float deltatime);
	virtual void Draw();
	virtual void Destroy();							//Dùng để xóa những con trỏ bên trong

	void DestroyProcess();
};