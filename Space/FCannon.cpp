#include "stdafx.h"
#include "FCannon.h"

FCannon::FCannon(Vec2 Pos, TEAM team, int num)
{
	m_Cannon = new Animation();
	m_Cannon->AddContinueFrame(L"Painting/Object/Tank/Enemy", 1, 1);
	m_Cannon->Init(7, true);
	m_Cannon->SetParent(this);
	m_Position = Pos;

	m_Barrel = Sprite::Create(L"Painting/Object/Tank/EnemyBarrel.png");
	m_Barrel->m_CenterPos.x = 85;
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

void FCannon::Update(float deltaTime, float time)
{
	ObjMgr->CollisionCheak(this, "Tile");
	Gravity();
	m_Barrel->m_Position = Vec2(m_Position.x - 160, m_Position.y - 35);

	if (INPUT->GetKey(VK_UP) == KeyState::PRESS && m_isGround)
	{
		m_Barrel->m_Rotation += D3DXToRadian(1);
	}
	if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS && m_isGround)
	{
		m_Barrel->m_Rotation -= D3DXToRadian(1);
	}
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
