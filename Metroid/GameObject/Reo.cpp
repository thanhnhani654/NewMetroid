#include "Reo.h"

void Reo::Initialize()
{
	Creature::Initialize();
	sprite.get()->SetAnimation("reo_greenyellow");

	box.DynamicInitialize(this, 24, 19);
	box.SetPivot(24 / 2, 9);
	GetMoveComponent()->OnAcceleration();
	//_SpeedY = 180;
	GetMoveComponent()->SetVelocity(0, -_SpeedY);
	GetMoveComponent()->SetAcceleration(-1.7, 0);
	test = false;
	bDetected = true;
	bParkOnTop = true;
}


void Reo::Update(float deltatime)
{
	
	GetMoveComponent()->UpdateMovement(deltatime);

	ChangeState();
	FixSomeWrongVelocity();
	
	/*if (GetPosition().y < _ClimaxPoint.y)
	{
		GetMoveComponent()->SetVelocity(GetMoveComponent()->GetVelocity().x, 120);
		GetMoveComponent()->SetAcceleration(-a, 0);
	}*/
}

void Reo::Draw()
{
	Creature::Draw();
}

void Reo::OnCollision(GameObject* object, float collideTime, int normalX, int normalY)
{
	if (!object->GetTagMethod()->isHasTag(eTag::TilesTag))
		return;
	//Chạm tường dưới bay ngược lên
	if (normalY < 0)
	{
		//ComeBack();
		float vecY = collideTime * GetMoveComponent()->GetVelocity().y * 0.1;
		GetMoveComponent()->SetVelocity(GetMoveComponent()->GetVelocity().x, vecY);
		bLanding = true;
		
	}
	//Chạm tường trên bay xuống
	if (normalY > 0)
	{
		bParkOnTop = true;
	}
	// Chạm tường ngang thì không bay vào
	if (normalX != 0)
	{
		GetMoveComponent()->SetVelocity(0, GetMoveComponent()->GetVelocity().y);
	}
	
}

void Reo::Destroy()
{

}

void Reo::FixSomeWrongVelocity()
{
	if (a > 0)
		if (GetMoveComponent()->GetVelocity().x < 0)
			GetMoveComponent()->SetVelocity(0, GetMoveComponent()->GetVelocity().y);
	if (a < 0)
		if (GetMoveComponent()->GetVelocity().x > 0)
			GetMoveComponent()->SetVelocity(0, GetMoveComponent()->GetVelocity().y);
}

void Reo::StartChase()
{
	GetMoveComponent()->SetVelocity(0, _SpeedY);
	//Tính khoảng cách của Reo với Samus
	_Sy =  GetPosition().y - Samus::getInstance()->GetPosition().y;
	_Sx = Samus::getInstance()->GetPosition().x - GetPosition().x;

	_Sy = bPerfectChase ? _Sy + 16 : _Sy - 16;

	//Lấy tọa độ của Samus
	_ClimaxPoint = Samus::getInstance()->GetPosition();
	
	_ClimaxPoint.y = bPerfectChase ? _ClimaxPoint.y - 32 : _ClimaxPoint.y;
	//Tính thời gian để Reo chạm Samus theo phương Y
	float ty = _Sy / -120;
	//Tính gia tốc cần để khi Reo chạm Samus theo phương Y thì cũng sẽ chạm Samus theo phương X
	a = (2 * _Sx) / (ty*ty);

	//Giới hạn gia tốc của Reo lại tránh Reo bắn tốc độ
	if (abs(a) > 0)
	{
		float temp = abs(a) / 200;
		a /= temp;
	}

	GetMoveComponent()->SetAcceleration(a, 0);

	/////////////////////////////////////////
	test = true;
	std::cout << "Gia toc: " << a << endl;
}

void Reo::ChangeState()
{
	switch (state)
	{
	case Idle:
		if (bDetected)
		{
			bDetected = false;
			bParkOnTop = false;
			bPerfectChase = !bPerfectChase;
			StartChase();

			state = TiepCan;
			bRollingOrFlying = Samus::getInstance()->IsFlying() || Samus::getInstance()->IsRolling();
			return;
		}
		FindSamus();
		break;
	case TiepCan:
		if (bPerfectChase)
		{
			if (Samus::getInstance()->IsRolling())
			{
				state = QuayVe;
				ComeBack();
				return;
			}
		}
		if (GetPosition().y < _ClimaxPoint.y)
		{
			state = QuayVe;
			ComeBack();
			std::cout << "at ClimaxPoint" << endl;
		}
		if (bLanding)
		{
			state = TruySat;
			Attack();
		}

		break;
	case TruySat:
		if (Samus::getInstance()->IsFlying())
		{
			state = QuayVe;
			bLanding = false;
			ComeBack();
			return;
		}
		this;
		cout << "Attacking" << endl;
		break;
	case QuayVe:
		if (bParkOnTop)
		{
			state = Idle;
			ResetIdle();
			bDetected = true;			//*
		}
		break;
	default:
		break;
	}
}

void Reo::ComeBack()
{
	GetMoveComponent()->SetVelocity(GetMoveComponent()->GetVelocity().x, -_SpeedY);
	GetMoveComponent()->SetAcceleration(-a, 0);
}

void Reo::Attack()
{
	if (_Sx < 0)
		GetMoveComponent()->SetVelocity(-_ChaseSpeedX, 0);
	else
		GetMoveComponent()->SetVelocity(_ChaseSpeedX, 0);
	this->GetMoveComponent()->SetAcceleration(0, 0);
}

void Reo::ResetIdle()
{
	GetMoveComponent()->SetVelocity(0, 0);
	GetMoveComponent()->SetAcceleration(0, 0);
	test = false;
	_ClimaxPoint.x = 0;
	_ClimaxPoint.y = 0;
}

void Reo::FindSamus()
{

}