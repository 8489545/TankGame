#include"stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Vec2 Pos,float Rotation)
{
	m_Bullet = Sprite::Create(L"Painting/Bullet.png");
	m_Bullet->SetParent(this);

	m_Position = Pos;
	m_Rotation = Rotation;

	A = m_Position;
	B = INPUT->GetRelativeMousePos();
	A -= B;
	D3DXVec2Normalize(&C, &A);

	m_BulletLife = 1.5f;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime, float time)
{
	ObjMgr->CollisionCheak(this, "Enemy");

	m_BulletLife -= deltaTime;
	if (m_BulletLife <= 0)
		SetDestroy(true);
	Translate(-C.x * 700 * deltaTime, -C.y * 700 * deltaTime);
}

void Bullet::Render()
{
	m_Bullet->Render();
}

void Bullet::OnCollision(Object* other)
{
	SetDestroy(true);
}
