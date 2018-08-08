#pragma once
#include "GameObject.h"
#include "../Component/Box2D.h"
#include <vector>

enum eDirection
{
	Left,
	Right,
	Top,
};

enum eBulletType
{
	Normal,
	Rocket,
	Freeze
};

class Bullet : public GameObject
{
private:
	//Component
	MoveComponent* move;
	Box2D box;
	
	//Properties
	float _Damage;
	float _LifeSpan;
	eDirection _Direction;
	eBulletType _Type;

	static bool bHaveRocket;
	
	static std::vector<Bullet*> listBullets;
public:
	#pragma region Inherit

	//virtual void Initialize();
	virtual void Ghost_Initialize(eDirection direction, eBulletType type,float x, float y);				//Initialize mà không lưu lại trong listObject
	//virtual void UpdateInput(float deltatime);
	virtual void Update(float deltatime);
	virtual void Draw();
	virtual void OnCollision(GameObject* object, float collideTime, int normalX, int normalY);
	virtual void Destroy();							//Dùng để xóa những con trỏ bên trong

	static Bullet* CreateBullet(eDirection direction, eBulletType type, float x, float y);
	static void UpdateBullets(float delatime);
	static void DrawBullets();
	// Dùng để tiêu diệt các bullet được đánh dấu tử
	static void DestroyBullets();

	#pragma endregion
};