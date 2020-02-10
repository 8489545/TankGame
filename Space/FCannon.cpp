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
	m_Hp = 100;
}

FCannon::~FCannon()
{
}

void FCannon::Gravity()
{
	static float vy = 0;
	vy += 50.f * dt;

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

void FCannon::Shot()
{
	//m_Position.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x;
	//m_Position.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;

	// ( Player::Getinst()->NowPos.x - m_BarrelEnd.x) (1 / cos(rot)) / power = t;

	/* | Player::Getinst()->NowPos.y = (m_Power * sin(rot))
	* ( Player::Getinst()->NowPos.x - m_BarrelEnd.x) (1 / cos(rot))
	/ power + 0.2 * 0.5f pow(( Player::Getinst()->NowPos.x - m_BarrelEnd.x) (1 / cos(rot)) / power ,2)+ m_BarrelEnd.y; */


	//tq 
	ObjMgr->AddObject(new CannonBall(rand() & 100, D3DXToRadian(rand() & 90), Vec2(m_BarrelEnd.x, m_BarrelEnd.y), Team), "CannonBall");
	GameMgr::GetInst()->SetTurn(TURN::PLAYER);
}

void FCannon::Update(float deltaTime, float time)
{
	ObjMgr->CollisionCheak(this, "Tile");
	ObjMgr->CollisionCheak(this, "CannonBall");
	ObjMgr->CollisionCheak(this, "Missile");
	ObjMgr->CollisionCheak(this, "Bomb");
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
	if (GameMgr::GetInst()->GetTurn() == TURN::ENEMY && Enemy::GetInst()->m_ControlTankNum == m_CannonNum && !Camera::GetInst()->m_CannonBall)
	{
		Camera::GetInst()->Follow(this);
		Shot();
	}
	else
	{
		Camera::GetInst()->Follow(nullptr);
	}
	if (m_Hp <= 0)
	{
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position), "Effect");
		ObjMgr->RemoveObject(this);
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
	if (other->m_Tag == "CannonBall" && other->Team == TEAM::PLAYER)
	{
		m_Hp -= 30;
	}
	if (other->m_Tag == "Missile" && other->Team == TEAM::PLAYER)
	{
		m_Hp -= 20;
	}
	if (other->m_Tag == "Bomb" && other->Team == TEAM::PLAYER)
	{
		m_Hp -= 40;
	}
}
