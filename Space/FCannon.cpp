#include "stdafx.h"
#include "FCannon.h"
#include"CannonBall.h"

FCannon::FCannon(Vec2 Pos, TEAM team, int num)
{
	m_Cannon = new Animation();
	m_Cannon->AddContinueFrame(L"Painting/Object/Tank/Enemy", 1, 1);
	m_Cannon->Init(7, true);
	m_Cannon->SetParent(this);
	m_Position = Pos;
	Team = team;
	m_CannonNum = num;

	m_Barrel = Sprite::Create(L"Painting/Object/Tank/EnemyBarrel.png");
}

FCannon::~FCannon()
{
}

void FCannon::Gravity()
{
	static float vy = 0;
	vy += 9.8f * dt;

	if (!m_isGround)
	{
		m_Position.y += vy;
	}
	else
		vy = 0;
}

void FCannon::SetEndPos()
{
	m_BarrelEnd.x = m_Barrel->m_Position.x + (-m_Barrel->m_Size.x / 2) * cos(m_Barrel->m_Rotation) - (m_Barrel->m_Size.y / 2) * sin(m_Barrel->m_Rotation);
	m_BarrelEnd.y = m_Barrel->m_Position.y + (-m_Barrel->m_Size.x / 2) * sin(m_Barrel->m_Rotation) + (m_Barrel->m_Size.y / 2) * cos(m_Barrel->m_Rotation);
}

void FCannon::Update(float deltaTime, float time)
{
	ObjMgr->CollisionCheak(this, "Tile");
	Player::GetInst()->SetEnemyPos(m_CannonNum, m_Position);
	Gravity();
	SetEndPos();
	m_Barrel->m_Position = Vec2(m_Position.x - 80, m_Position.y - 35);

	if (INPUT->GetKey(VK_UP) == KeyState::PRESS && m_isGround)
	{
		m_Barrel->m_Rotation += D3DXToRadian(1);
	}
	if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS && m_isGround)
	{
		m_Barrel->m_Rotation -= D3DXToRadian(1);
	}
	if (INPUT->GetKey(VK_SPACE) == KeyState::UP && m_isGround)
		ObjMgr->AddObject(new CannonBall(10, m_Barrel->m_Rotation, m_BarrelEnd, Team), "CannonBall");
}

void FCannon::Render()
{
	m_Cannon->Render();
	m_Barrel->Render();
}

void FCannon::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
	{
		m_isGround = true;
	}
}
