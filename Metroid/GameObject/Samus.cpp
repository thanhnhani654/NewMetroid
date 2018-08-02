#include "Samus.h"

void Samus::Initialize()
{
	Creature::Initialize();
	sprite.get()->SetAnimation("char_run");
	GetMoveComponent()->EnableGravity();
	GetMoveComponent()->SetSpeed(150);

	//Condition Initialize
	bFlying = false;
	bMoving = false;
	bLookUp = false;
	bAttack = false;
	bCrouch = false;
	bInput = true;
	_state = eSamusState::Stand;
}

void Samus::Ghost_Initialize(){}

void Samus::UpdateInput(float deltatime)
{
	if (bInput)
		_ProcessKeyBoard();
	ControllerUpdate();
}

void Samus::Update(float deltatime)
{
	GetMoveComponent()->UpdateMovement(deltatime);
}

void Samus::Draw()
{
	Creature::Draw();
}

void Samus::Destroy()
{}

void Samus::OnKeyDown(int Keycode)
{
	switch (Keycode)
	{
	/*case DIK_A:
		GetMoveComponent()->MoveLeft();
		break;
	case DIK_D:
		GetMoveComponent()->MoveRight();
		break;*/
	}
}

//Animation Manager
void Samus::UpdateState(float deltatime)
{
	switch (_state)
	{
	case eSamusState::Stand:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::Jump;
		else if (!bMoving == false)
			_state = eSamusState::MovingOnGround;
		else if (!bLookUp == false)
			_state = eSamusState::StandLookUp;
		else if (!bAttack == false)
			_state = eSamusState::StandAttack;
		#pragma endregion
		break;
	case eSamusState::StandAttack:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpAttack;
		else if (!bMoving == false)
			_state = eSamusState::MovingOnGroundAtack;
		else if (!bLookUp == false)
			_state = eSamusState::StandLookUpAttack;
		else if (!bAttack == true)
			_state = eSamusState::Stand;
		#pragma endregion
		break;
	case eSamusState::StandLookUp:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpLookUp;
		else if (!bMoving == false)
			_state = eSamusState::MovingOnGroundLookUp;
		else if (!bLookUp == true)
			_state = eSamusState::Stand;
		else if (!bAttack == false)
			_state = eSamusState::StandLookUpAttack;
		#pragma endregion
		break;
	case eSamusState::StandLookUpAttack:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpLookUpAttack;
		else if (!bMoving == false)
			_state = eSamusState::MovingOnGroundLookUpAttack;
		else if (!bLookUp == true)
			_state = eSamusState::StandAttack;
		else if (!bAttack == true)
			_state = eSamusState::StandLookUp;
		#pragma endregion
		break;
	case eSamusState::MovingOnGround:
		#pragma region Condition Checker
		//Need Special Condition
		if (!bFlying == false)
			_state = eSamusState::Santo;
		else if (!bMoving == true)
			_state = eSamusState::Stand;
		else if (!bLookUp == false)
			_state = eSamusState::MovingOnGroundLookUp;
		else if (!bAttack == false)
			_state = eSamusState::MovingOnGroundAtack;
		#pragma endregion
		break;
	case eSamusState::MovingOnGroundAtack:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpAttack;
		else if (!bMoving == true)
			_state = eSamusState::StandAttack;
		else if (!bLookUp == false)
			_state = eSamusState::MovingOnGroundLookUpAttack;
		else if (!bAttack == true)
			_state = eSamusState::MovingOnGround;
		#pragma endregion
		break;
	case eSamusState::MovingOnGroundLookUp:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpLookUp;
		else if (!bMoving == true)
			_state = eSamusState::StandLookUp;
		else if (!bLookUp == true)
			_state = eSamusState::MovingOnGround;
		else if (!bAttack == false)
			_state = eSamusState::MovingOnGroundLookUpAttack;
		#pragma endregion
		break;
	case eSamusState::MovingOnGroundLookUpAttack:
		#pragma region Condition Checker
		if (!bFlying == false)
			_state = eSamusState::JumpLookUpAttack;
		else if (!bMoving == true)
			_state = eSamusState::StandLookUpAttack;
		else if (!bLookUp == true)
			_state = eSamusState::MovingOnGroundAtack;
		else if (!bAttack == true)
			_state = eSamusState::MovingOnGroundLookUp;
		#pragma endregion
		break;
	case eSamusState::Jump:
		#pragma region Condition Checker
		if (!bFlying == true)
			_state = eSamusState::Stand;
		//else if (!bMoving == false)
		//	_state = eSamusState::StandAttack;
		else if (!bLookUp == false)
			_state = eSamusState::JumpLookUp;
		else if (!bAttack == false)
			_state = eSamusState::JumpAttack;
		#pragma endregion
		break;
	case eSamusState::JumpAttack:
		#pragma region Condition Checker
		if (!bFlying == true)
			_state = eSamusState::StandAttack;
		//else if (!bMoving == false)
		//	_state = eSamusState::StandAttack;
		else if (!bLookUp == false)
			_state = eSamusState::JumpLookUpAttack;
		else if (!bAttack == true)
			_state = eSamusState::Jump;
		#pragma endregion
		break;
	case eSamusState::JumpLookUp:
		#pragma region Condition Checker
		if (!bFlying == true)
			_state = eSamusState::StandLookUp;
		//else if (!bMoving == false)
		//	_state = eSamusState::StandAttack;
		else if (!bLookUp == true)
			_state = eSamusState::Jump;
		else if (!bAttack == false)
			_state = eSamusState::JumpLookUpAttack;
		#pragma endregion
		break;
	case eSamusState::JumpLookUpAttack:
		#pragma region Condition Checker
		if (!bFlying == true)
			_state = eSamusState::StandLookUpAttack;
		//else if (!bMoving == false)
		//	_state = eSamusState::StandAttack;
		else if (!bLookUp == true)
			_state = eSamusState::JumpAttack;
		else if (!bAttack == true)
			_state = eSamusState::JumpLookUp;
		#pragma endregion
		break;
	//case eSamusState::JumpMove:
		/**/
	//	break;
	case eSamusState::Santo:
		#pragma region Condition Checker
		if (!bFlying == true)
			_state = eSamusState::Stand;
		//else if (!bMoving == false)
		//	_state = eSamusState::StandAttack;
		else if (!bLookUp == false)
			_state = eSamusState::JumpLookUp;
		else if (!bAttack == false)
			_state = eSamusState::JumpAttack;
		#pragma endregion
		break;
	//case eSamusState::JumpMoveAttack:
	//	/**/
	//	break;
	//case eSamusState::JumpMoveLookUp:
	//	/**/
	//	break;
	//case eSamusState::JumpMoveLookUpAttack:
	//	/**/
	//	break;
	default:
		break;
	}

	
}

//Character Controller
void Samus::ControllerUpdate()
{
	Move();
}

void Samus::Move()
{
	if (IsKeyDown(DIK_D))
	{
		GetMoveComponent()->MoveRight();
		sprite.get()->FlipRight();
	}
	else if (IsKeyDown(DIK_A))
	{
		GetMoveComponent()->MoveLeft();
		sprite.get()->FlipLeft();
	}
	else
	{
		GetMoveComponent()->IdleX();
	}
}
