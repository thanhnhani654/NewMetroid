#include "Samus.h"

void Samus::Initialize()
{
	Creature::Initialize();
	sprite.get()->SetAnimation("char_run");
	GetMoveComponent()->EnableGravity();
	GetMoveComponent()->SetSpeed(150);

	box.DynamicInitialize(this, 16, 32);

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
	UpdateState(deltatime);
	this;
}

void Samus::Draw()
{
	Creature::Draw();
}

void Samus::OnCollision(GameObject* object, float collideTime, int normalX, int normalY)
{
	if (object->GetTagMethod()->isHasTag(eTag::TilesTag))
	{
		if (collideTime >= 0 || collideTime < 0.1)
		{
			if (collideTime < 0.1)
				collideTime = 0;
			float vecX = GetMoveComponent()->GetVelocity().x;
			float vecY = GetMoveComponent()->GetVelocity().y;
			if (normalX != 0)
			{
				vecX = collideTime * GetMoveComponent()->GetVelocity().x * 0.1;
			}

			if (normalY > 0)
			{
				vecY = collideTime * GetMoveComponent()->GetVelocity().y * 0.1;
				//if (collideTime != 0)
					//cout << "Va cham ben tren" << endl;
			}

			if (normalY < 0)
			{
				this;
				vecY = collideTime * GetMoveComponent()->GetVelocity().y * 0.1;		
				bFlying = false;
				if (collideTime != 0)
				{
					//cout << "CollideTime: " << collideTime << "\tVeclocity: " << vecY << "\tPosition: " << GetPosition().y - 16 << "\tObject: " << object->GetPosition().y + 8 << endl;
					//cout << "Va cham ben duoi" << endl;
				}
			}

			GetMoveComponent()->SetVelocity(vecX, vecY);
		}
	}
}

void Samus::Destroy()
{}

void Samus::OnKeyDown(int Keycode)
{
	switch (Keycode)
	{
	case DIK_SPACE:

		if (!bFlying && !bCrouch)
		{			
			GetMoveComponent()->Jump();
			
			cout << "Jumping" << endl;
			bFlying = true;
		}

		if (bCrouch)
			bCrouch = false;

		break;
	case DIK_S:
		if (!bFlying)
		{
			bCrouch = true;
		}
	}
}

//Animation Manager
void Samus::UpdateState(float deltatime)
{
	_prevState = _state;
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
		else if (!bCrouch == false)
		{
			_state = eSamusState::Rolling;
			box.SetSize(16, 16);
		}
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
	case eSamusState::Rolling:
		#pragma region Condition Checker
		if (!bFlying == false)
		{
			bool checker = false;
			box.SetSize(16, 32);
			SetPosition(GetPosition().x, GetPosition().y + 16);
			for (int i = 0; i < Box2D::listBox.size(); i++)
			{
				if (&box == &Box2D::listBox[i].get())
					continue;
				if (Box2D::listBox[i].get().getGameObject()->GetTagMethod()->isHasTag(eTag::TilesTag))
					if (Collision::getInstance()->IsIntersection(Box2D::listBox[i].get().GetBox(), box.GetBox()))
					{
						checker = true;
						break;
					}
			}
			if (!checker)
				_state = eSamusState::Stand;
			else
			{
				box.SetSize(16, 16);
				SetPosition(GetPosition().x, GetPosition().y - 16);
				bCrouch = true;
			}
		}
		else if (!bAttack == false)
		{
			bool checker = false;
			box.SetSize(16, 32);
			SetPosition(GetPosition().x, GetPosition().y + 16);
			for (int i = 0; i < Box2D::listBox.size(); i++)
			{
				if (&box == &Box2D::listBox[i].get())
					continue;
				if (Box2D::listBox[i].get().getGameObject()->GetTagMethod()->isHasTag(eTag::TilesTag))
					if (Collision::getInstance()->IsIntersection(Box2D::listBox[i].get().GetBox(), box.GetBox()))
					{
						checker = true;
						break;
					}
			}
			if (!checker)
				_state = eSamusState::StandAttack;
			else
			{
				box.SetSize(16, 16);
				SetPosition(GetPosition().x, GetPosition().y - 16);
				bCrouch = true;
			}
		}
		else if (!bCrouch == true)
		{
			bool checker = false;
			box.SetSize(16, 32);
			SetPosition(GetPosition().x, GetPosition().y + 16);
			for (int i = 0; i < Box2D::listBox.size(); i++)
			{
				if (&box == &Box2D::listBox[i].get())
					continue;
				if (Box2D::listBox[i].get().getGameObject()->GetTagMethod()->isHasTag(eTag::TilesTag))
					if (Collision::getInstance()->IsIntersection(Box2D::listBox[i].get().GetBox(), box.GetBox()))
					{
						checker = true;
						break;
					}
			}
			if (!checker)
				_state = eSamusState::Stand;
			else
			{
				box.SetSize(16, 16);
				SetPosition(GetPosition().x, GetPosition().y - 16);
				bCrouch = true;
			}
		}

		
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

	if (_prevState != _state)
	{
		switch (_state)
		{
		case eSamusState::Stand:
			if (!bCrouch)
				sprite->SetAnimation("char_stand");
			else
				sprite->SetAnimation("char_roll");
			break;
		case eSamusState::StandAttack:
			sprite->SetAnimation("char_stand_shoot");
			break;
		case eSamusState::StandLookUp:
			break;
		case eSamusState::StandLookUpAttack:
			sprite->SetAnimation("char_shoot_up");
			break;
		case eSamusState::MovingOnGround:
			sprite->SetAnimation("char_run");
			break;
		case eSamusState::MovingOnGroundAtack:
			sprite->SetAnimation("char_run_shoot");
			break;
		case eSamusState::MovingOnGroundLookUp:
			break;
		case eSamusState::MovingOnGroundLookUpAttack:
			sprite->SetAnimation("char_run_shoot_up");
			break;
		case eSamusState::Jump:
			sprite->SetAnimation("char_jump");
			break;
		case eSamusState::JumpAttack:
			break;
		case eSamusState::JumpLookUp:
			break;
		case eSamusState::JumpLookUpAttack:
			break;
		case eSamusState::Santo:
			sprite->SetAnimation("char_flip");
			break;
		case eSamusState::Rolling:
			sprite->SetAnimation("char_roll");
			break;

		}
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
		bMoving = true;
	}
	else if (IsKeyDown(DIK_A))
	{
		GetMoveComponent()->MoveLeft();
		sprite.get()->FlipLeft();
		bMoving = true;
	}
	else 
	{
		GetMoveComponent()->IdleX();
		bMoving = false;
	}

	if (IsKeyDown(DIK_SPACE))
	{
		
	}
}
