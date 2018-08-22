#include "Zoomer.h"

void Zoomer::Initialize()
{
	Creature::Initialize();

	sprite.get()->SetAnimation("zoomer_orange_on");

	speed = 200;
	GetMoveComponent()->SetSpeed(speed - 100);
	GetMoveComponent()->OnAcceleration();
	GetMoveComponent()->SetGravity(500000);
	GetMoveComponent()->SetLimitedSpeed(speed);

	box.DynamicInitialize(this, 16, 16);
	box.SetPivot(16 / 2, 16 / 2);

	bGoRight = true;
	state = eZoomerState::OnZState;

	bChangeStateOnOutCollision = false;
}

void Zoomer::Update(float deltatime)
{
	
	ChangeState();
	
	AiMove();
	SetGravity();
	GetMoveComponent()->UpdateMovement(deltatime);
	
	
	bChangeStateOnOutCollision = true;
	this;
}

void Zoomer::Draw()
{
	Creature::Draw();
}

void Zoomer::OnCollision(GameObject * object, float collideTime, int normalX, int normalY)
{

	bChangeStateOnOutCollision = false;
	switch (state)
	{
	case OnZState:
	case UnderZState:
		GetMoveComponent()->SetVelocity(GetMoveComponent()->GetVelocity().x, 0);
		break;
	case LeftZState:
	case RightZState:
		GetMoveComponent()->SetVelocity(0, GetMoveComponent()->GetVelocity().y);
		break;
	default:
		break;
	}
	if (collideTime >= 0)
		switch (state)
		{
		case OnZState:
		case UnderZState:
			if (normalX != 0)
				bChangeState = true;
			break;
		case LeftZState:
		case RightZState:
			if (normalY != 0)
				bChangeState = true;
			break;
		default:
			break;
		}
}

void Zoomer::Destroy()
{
	Creature::Destroy();
}


//Method
void Zoomer::ChangeState()
{
	if (bChangeState && !bChangeStateOnOutCollision)
	{
		bChangeState = false;

		switch (state)
		{
		case eZoomerState::OnZState:
			if (bGoRight)
			{
				state = LeftZState;
				sprite.get()->SetAnimation("zoomer_orange_left");
			}
			else
			{
				state = RightZState;
				sprite.get()->SetAnimation("zoomer_orange_right");
			}
			break;
		case eZoomerState::UnderZState:
			if (bGoRight)
			{
				state = RightZState;
				sprite.get()->SetAnimation("zoomer_orange_right");
			}
			else
			{
				state = LeftZState;
				sprite.get()->SetAnimation("zoomer_orange_left");
			}
			break;
		case eZoomerState::LeftZState:
			if (bGoRight)
			{
				state = UnderZState;
				sprite.get()->SetAnimation("zoomer_orange_under");
			}
			else
			{
				state = OnZState;
				sprite.get()->SetAnimation("zoomer_orange_on");
			}
			break;
		case eZoomerState::RightZState:
			if (bGoRight)
			{
				state = OnZState;
				sprite.get()->SetAnimation("zoomer_orange_on");
			}
			else
			{
				state = UnderZState;
				sprite.get()->SetAnimation("zoomer_orange_under");
			}
			break;
		}
	}
	if (bChangeStateOnOutCollision)
	{
		bChangeStateOnOutCollision = false;
		//cout << "ChangeStateOnOutCollision!" << endl;
		this;
		switch (state)
		{
		case eZoomerState::OnZState:
			if (bGoRight)
			{
				state = RightZState;
				sprite.get()->SetAnimation("zoomer_orange_right");
			}
			else
			{
				state = LeftZState;
				sprite.get()->SetAnimation("zoomer_orange_left");
			}
			break;
		case eZoomerState::UnderZState:
			if (bGoRight)
			{
				state = LeftZState;
				sprite.get()->SetAnimation("zoomer_orange_left");
			}
			else
			{
				state = RightZState;
				sprite.get()->SetAnimation("zoomer_orange_right");
			}
			break;
		case eZoomerState::LeftZState:
			if (bGoRight)
			{
				state = OnZState;
				sprite.get()->SetAnimation("zoomer_orange_on");
			}
			else
			{
				state = UnderZState;
				sprite.get()->SetAnimation("zoomer_orange_under");
			}
			break;
		case eZoomerState::RightZState:
			if (bGoRight)
			{
				state = UnderZState;
				sprite.get()->SetAnimation("zoomer_orange_under");
			}
			else
			{
				state = OnZState;
				sprite.get()->SetAnimation("zoomer_orange_on");
			}
			break;
		}
	}
}

void Zoomer::SetGravity()
{
	switch (state)
	{
	case OnZState:
		GetMoveComponent()->SetAcceleration(0, -GetMoveComponent()->GetGravity());
		break;
	case UnderZState:
		GetMoveComponent()->SetAcceleration(0, GetMoveComponent()->GetGravity());
		break;
	case LeftZState:
		GetMoveComponent()->SetAcceleration(GetMoveComponent()->GetGravity(), 0);
		break;
	case RightZState:
		GetMoveComponent()->SetAcceleration(-GetMoveComponent()->GetGravity(), 0);
		break;
	default:
		break;
	}
}

void Zoomer::AiMove()
{
	switch (state)
	{
	case OnZState:
		if (bGoRight)
			GetMoveComponent()->MoveRight();
		else
			GetMoveComponent()->MoveLeft();
		GetMoveComponent()->IdleY();
		break;
	case UnderZState:
		if (bGoRight)
			GetMoveComponent()->MoveLeft();
		else
			GetMoveComponent()->MoveRight();
		GetMoveComponent()->IdleY();
		break;
	case LeftZState:
		if (bGoRight)
			GetMoveComponent()->MoveUp();
		else
			GetMoveComponent()->MoveDown();
		GetMoveComponent()->IdleX();
		break;
	case RightZState:
		if (bGoRight)
			GetMoveComponent()->MoveDown();
		else
			GetMoveComponent()->MoveUp();
		GetMoveComponent()->IdleX();
		break;
	default:
		break;
	}
}