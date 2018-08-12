#pragma once
#include "Creature.h"
#include "../Controllable.h"
#include "../Component/Collision.h"
#include "Bullet.h"
#include "../Component/SceneActor.h"
#include "Item.h"

enum class eSamusState			// Bool Flying, Bool Moving, Bool LookUp, Bool Attacking
{
	Stand,						// Flying = false;	Moving = false;	LookUp = false;	Attacking = false;
	StandAttack,				// Flying = false;	Moving = false;	LookUp = false;	Attacking = true;
	StandLookUp,				// Flying = false;	Moving = false;	LookUp = true;	Attacking = false;
	StandLookUpAttack,			// Flying = false;	Moving = false;	LookUp = true;	Attacking = true;
	MovingOnGround,				// Flying = false;	Moving = true;	LookUp = false;	Attacking = false;
	MovingOnGroundAtack,		// Flying = false;	Moving = true;	LookUp = false;	Attacking = true;
	MovingOnGroundLookUp,		// Flying = false;	Moving = true;	LookUp = true;	Attacking = false;
	MovingOnGroundLookUpAttack,	// Flying = false;	Moving = true;	LookUp = true;	Attacking = true;
	Jump,						// Flying = true;	Moving = false;	LookUp = false;	Attacking = false;
	JumpAttack,					// Flying = true;	Moving = false;	LookUp = false;	Attacking = true;
	JumpLookUp,					// Flying = true;	Moving = false;	LookUp = true;	Attacking = false;
	JumpLookUpAttack,			// Flying = true;	Moving = false;	LookUp = true;	Attacking = true;
	//JumpMove,					// Flying = true;	Moving = true;	LookUp = false;	Attacking = false;
	Santo,						// Flying = true;	Moving = true;	LookUp = false;	Attacking = false;	in Special Condition and only change when previous State is Moving
	//JumpMoveAttack,				// Flying = true;	Moving = true;	LookUp = false;	Attacking = true;
	//JumpMoveLookUp,				// Flying = true;	Moving = true;	LookUp = true;	Attacking = false;
	//JumpMoveLookUpAttack,		// Flying = true;	Moving = true;	LookUp = true;	Attacking = true;4
	Rolling,

};

class Samus : public Creature, Controllable
{
private:
	
	static Samus* instance;

	// Điều kiện để một state hoạt động
	bool bFlying;
	bool bLookUp;
	bool bMoving;
	bool bAttack;
	bool bCrouch;
	bool bInput;

	//Some order varible
	eDirection direction;

	eSamusState _state;
	eSamusState _prevState;

	void UpdateState(float deltatime);
	void Stand();

	// Thực hiện nhảy cao
	void HighJump(float deltatime);
	bool bjumpRelease;						// Kiểm tra phím Jump có được thả kể từ khi bấm
	float jumpTime;							// Thời gian giữ phím Jump để được độ cao tối đa
	float jumpSpan;							// Thời gian đếm ngược cho đến khi đạt độ cao tối đa
	
	// Fire Bullet
	bool bHaveRocket;
	bool bHaveFreezeBullet;
	float _FireRate;						// Số viên đạn bắn được trong 1s
	float _FireTime;
	eBulletType _BulletType;
	D3DXVECTOR2 _FirePos;					// Vị trí viên đạn xuất hiện
	std::vector<Bullet*> bulletsVector;
	void Fire(float deltatime);

	void Move();
	void ControllerUpdate();

public:
	#pragma region Inherit

	//Inherit From Creature
	void Initialize();
	void Ghost_Initialize();				//Initialize mà không lưu lại trong listObject
	void UpdateInput(float deltatime);
	void Update(float deltatime);
	void Draw();
	void OnCollision(GameObject* object, float collideTime, int normalX, int normalY);
	void Destroy();							//Dùng để xóa những con trỏ bên trong

	//Inherit From Controllable
	void OnKeyDown(int Keycode);
	void OnKeyUp(int Keycode);

	#pragma endregion

	
	static Samus* getInstance();
};