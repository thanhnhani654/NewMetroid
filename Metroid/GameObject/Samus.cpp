#include "Samus.h"

void Samus::Initialize()
{
	Creature::Initialize();
	sprite.get()->SetAnimation("char_run");
	GetMoveComponent()->EnableGravity();
	GetMoveComponent()->SetSpeed(150);

	box.DynamicInitialize(this, 16, 26);
	box.SetPivot(8, 16);

	//Condition Initialize
	bFlying = false;
	bMoving = false;
	bLookUp = false;
	bAttack = false;
	bCrouch = false;
	bInput = true;
	_state = eSamusState::Stand;
	direction = eDirection::Left;
	bHaveRocket = false;
	bHaveFreezeBullet = false;

	jumpTime = 0.5;
	jumpSpan = jumpTime;

	// Bullet Fire
	_FireRate = 10;
	_FireTime = 0;
	_FirePos.x = 0;
	_FirePos.y = 0;
	_BulletType = eBulletType::Normal;
	
}

void Samus::Ghost_Initialize(){}

void Samus::UpdateInput(float deltatime)
{
	if (bInput)
		_ProcessKeyBoard();
	ControllerUpdate();
	//Update Animation
	UpdateState(deltatime);
}

void Samus::Update(float deltatime)
{
	Fire(deltatime);
	//Update Movement
	GetMoveComponent()->UpdateMovement(deltatime);
	HighJump(deltatime);
	
	this;
}

void Samus::Draw()
{
	Creature::Draw();
}

void Samus::OnCollision(GameObject* object, float collideTime, int normalX, int normalY)
{
	if (object->GetTagMethod()->isHasTag(eTag::ItemTag))
	{
		cout << "eatItem" << endl;
		if (((Item*)(object))->GetItemType() == eItem::RocketItem)
			bHaveRocket = true;
		object->SetDeleted();
		SceneActor::getInstance()->PauseFor(2.0f);
	}
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
			bjumpRelease = false;
		}

		if (bCrouch)
			bCrouch = false;

		break;
	case DIK_S:
		if (!bFlying)
		{
			bCrouch = true;
		}
		break;
	case DIK_R:
		switch (_BulletType)
		{
		case eBulletType::Normal:
			if (bHaveRocket)
				_BulletType = eBulletType::Rocket;
			break;
		case eBulletType::Rocket:
			if (!bHaveFreezeBullet)
				_BulletType = eBulletType::Normal;
			else
				_BulletType = eBulletType::Freeze;
			break;
		case eBulletType::Freeze:
			if (bHaveRocket)
				_BulletType = eBulletType::Rocket;
			break;
		}
		break;
	}
}

void Samus::OnKeyUp(int Keycode)
{
	switch (Keycode)
	{
	case DIK_SPACE:
		bjumpRelease = true;
		jumpSpan = jumpTime;
		break;
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetPivot(8, 8);
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
			box.SetSize(16, 26);
			box.SetPivot(8, 16);
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
				box.SetPivot(8, 8);
				SetPosition(GetPosition().x, GetPosition().y - 16);
				bCrouch = true;
			}
		}
		else if (!bAttack == false)
		{
			bool checker = false;
			box.SetSize(16, 26);
			box.SetPivot(8, 16);
			SetPosition(GetPosition().x, GetPosition().y + 16);
			std::vector<Box2D*> templist = Box2D::listBox_Ptr;
			for (int i = 0; i < templist.size(); i++)
			{
				if (&box == templist[i])
					continue;
				if (templist[i]->getGameObject()->GetTagMethod()->isHasTag(eTag::TilesTag))
					if (Collision::getInstance()->IsIntersection(templist[i]->GetBox(), box.GetBox()))
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
				box.SetPivot(8, 8);
				SetPosition(GetPosition().x, GetPosition().y - 16);
				bCrouch = true;
			}
		}
		else if (!bCrouch == true)
		{
			bool checker = false;
			box.SetSize(16, 26);
			box.SetPivot(8, 16);
			SetPosition(GetPosition().x, GetPosition().y + 16);
			std::vector<Box2D*> templist = Box2D::listBox_Ptr;
			for (int i = 0; i < templist.size(); i++)
			{
				if (&box == templist[i])
					continue;
				if (templist[i]->getGameObject()->GetTagMethod()->isHasTag(eTag::TilesTag))
					if (Collision::getInstance()->IsIntersection(templist[i]->GetBox(), box.GetBox()))
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
				box.SetPivot(8, 8);
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
	if (IsKeyDown(DIK_W))
	{
		bLookUp = true;
	}
	else
	{
		bLookUp = false;
	}
}

void Samus::Move()
{
	if (IsKeyDown(DIK_D))
	{
		GetMoveComponent()->MoveRight();
		sprite.get()->FlipRight();
		bMoving = true;
		direction = eDirection::Right;
	}
	else if (IsKeyDown(DIK_A))
	{
		GetMoveComponent()->MoveLeft();
		sprite.get()->FlipLeft();
		bMoving = true;
		direction = eDirection::Left;
	}
	else 
	{
		GetMoveComponent()->IdleX();
		bMoving = false;
	}
}

void Samus::HighJump(float deltatime)
{
	if (!bjumpRelease && bFlying && jumpSpan > 0)
	{
		jumpSpan -= deltatime;
		float delta = jumpSpan >= 0 ? deltatime : deltatime + jumpSpan;

		GetMoveComponent()->SetAcceleration(GetMoveComponent()->GetAcceleration().x, GetMoveComponent()->GetAcceleration().y + delta *500);
	}
}

void Samus::Fire(float deltatime)
{
	bAttack = false;
	if (bCrouch)
		return;
	if (!IsKeyDown(DIK_J))
		return;
	_FireTime += deltatime;
	if (_FireTime < 1.0f / _FireRate)
		return;
	_FireTime = 0;
	if (!bLookUp)
		Bullet::CreateBullet(direction, _BulletType, _FirePos.x + GetPosition().x, _FirePos.y + GetPosition().y);
	else
		Bullet::CreateBullet(eDirection::Top, _BulletType, _FirePos.x + GetPosition().x, _FirePos.y + GetPosition().y);
	//bAttack = true;
}