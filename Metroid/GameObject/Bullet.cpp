#include "Bullet.h"

std::vector<Bullet*> Bullet::listBullets;
bool Bullet::bHaveRocket;

void Bullet::Ghost_Initialize(eDirection direction, eBulletType type, float x, float y)
{
	GameObject::Ghost_Initialize();
	move = new MoveComponent();
	move->Initialize(GetPosition_Ptr(), GetVelocity_Ptr());
	move->DisableGravity();
	move->SetSpeed(200);

	box.DynamicInitialize(this, 4, 4);
	box.SetPivot(2, 2);

	
	this->_Direction = direction;
	switch (_Direction)
	{
	case Left:
		move->MoveLeft();
		sprite.get()->FlipLeft();
		break;
	case Right:
		move->MoveRight();
		break;
	case Top:
		move->MoveUp();
		break;
	}

	listBullets.push_back(this);

	SetPosition(x,y);
	_Type = type;
	switch (_Type)
	{
	case Normal:
		sprite.get()->SetAnimation("bullet");
		_Damage = 1.0f;
		_LifeSpan = 0.3f;
		break;
	case Rocket:
		if (direction != eDirection::Top)
			sprite.get()->SetAnimation("rocket");
		else
			sprite.get()->SetAnimation("rocket_up");
		_Damage = 1.0f;
		_LifeSpan = 1.0f;
		break;
	case Freeze:
		sprite.get()->SetAnimation("bullet");
		//sprite.get()->SetAnimation("bullet_freeze");
		_Damage = 1.0f;
		_LifeSpan = 0.3f;
		break;
	default:
		break;
	}
	
}

void Bullet::Update(float deltatime)
{
	move->UpdateMovement(deltatime);
	if (_LifeSpan < 0)
	{
		if (_Type == eBulletType::Rocket)
			bHaveRocket = false;
		this->SetDeleted();
	}
	_LifeSpan -= deltatime;

}

void Bullet::Draw()
{
	GameObject::Draw();
}

void Bullet::OnCollision(GameObject* object, float collideTime, int normalX, int normalY)
{
	if (object->GetTagMethod()->isHasTag(eTag::TilesTag))
	{
		SetDeleted();
		cout << "SetDeleted" << "\tX: " << GetPosition().x << "\tY: " << GetPosition().y << endl;
		if (_Type == eBulletType::Rocket)
			bHaveRocket = false;
	}
}

void Bullet::Destroy()
{
	GameObject::Destroy();
	delete move;
	box.SetDeleted();
}

Bullet* Bullet::CreateBullet(eDirection direction, eBulletType type, float x, float y)
{
	if (type == eBulletType::Rocket)
	{
		if (bHaveRocket)
			return nullptr;
		bHaveRocket = true;
	}

	Bullet* bullet = new Bullet();
	bullet->Ghost_Initialize(direction, type, x, y);

	
	return bullet;
}

void Bullet::UpdateBullets(float delatime)
{
	for (std::vector<Bullet*>::iterator it = listBullets.begin(); it != listBullets.end(); it++)
	{
		(*it)->Update(delatime);
	}
}

void Bullet::DrawBullets()
{
	for (std::vector<Bullet*>::iterator it = listBullets.begin(); it != listBullets.end(); it++)
	{
		(*it)->Draw();
	}
}

void Bullet::DestroyBullets()
{
	int mark = -1;
	std::vector<Bullet*>::iterator it;
	for (it = listBullets.begin(); it != listBullets.end(); it++)
	{
		if ((*it)->isDeleted())
		{
			(*it)->Destroy();
			delete (*it);
			(*it) = nullptr;
			mark = 1;
			break;
		}
	}
	if (mark != (-1))
	{
		listBullets.erase(it);
		listBullets.shrink_to_fit();
		DestroyBullets();
	}
}