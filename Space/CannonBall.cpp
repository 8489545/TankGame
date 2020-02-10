#include "stdafx.h"
#include "CannonBall.h"

CannonBall::CannonBall(float power, float rot, Vec2 Pos, TEAM team)
{
	m_CannonBall = Sprite::Create(L"Painting/Object/CannonBall.png");
	m_CannonBall->SetParent(this);

	m_Missile = Sprite::Create(L"Painting/Object/Missile.png");
	m_Missile->SetParent(this);

	m_Pos = Pos;
	m_Power = power / 3 + 5;
	m_Rotation = rot;
	m_StartingRotation = rot;
	GR = 0.2f;
	t = 0;

	Team = team;

	if (Team == TEAM::ENEMY)
	{
		m_Power *= -1;
	}
}

CannonBall::~CannonBall()
{
}

void CannonBall::Update(float deltaTime, float time)
{
	Camera::GetInst()->m_CannonBall = true;
	ObjMgr->CollisionCheak(this, "Tile");
	ObjMgr->CollisionCheak(this, "Tank");
	ObjMgr->CollisionCheak(this, "Enemy");
	Camera::GetInst()->Follow(this);
	m_Position.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x ;
	m_Position.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;

	t++;

	m_NextPos.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x;
	m_NextPos.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;


	SetRotation();
	SetVertex();

	if (m_Position.x >= Camera::GetInst()->m_MaxX + 1920 || m_Position.x <= Camera::GetInst()->m_MinX)
		SetDestroy(true);
}

void CannonBall::Render()
{
	if(m_Tag == "CannonBall")
		m_CannonBall->Render();
	if (m_Tag == "Missile")
		m_Missile->Render();
}

void CannonBall::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
	{
		if (CollisionMgr::GetInst()->LineToLineCollide(Vertex1, Vertex2, other->m_LinePos1, other->m_LinePos2) 
			|| CollisionMgr::GetInst()->LineToLineCollide(Vertex2, Vertex3, other->m_LinePos1, other->m_LinePos2))
		{
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position),"Effect");
			Camera::GetInst()->m_CannonBall = false;
			Camera::GetInst()->Follow(nullptr);
			if (Team == TEAM::PLAYER)
				GameMgr::GetInst()->SetTurn(TURN::ENEMY);
			else if (Team == TEAM::ENEMY)
				GameMgr::GetInst()->SetTurn(TURN::PLAYER);
			Enemy::GetInst()->ChooseControlTank();
			SetDestroy(true);
		}
	}
	if (other->m_Tag == "Tank")
	{
		if (Team == TEAM::ENEMY)
		{
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position), "Effect");
			Camera::GetInst()->m_CannonBall = false;
			Camera::GetInst()->Follow(nullptr);
			if (Team == TEAM::PLAYER)
				GameMgr::GetInst()->SetTurn(TURN::ENEMY);
			else if (Team == TEAM::ENEMY)
				GameMgr::GetInst()->SetTurn(TURN::PLAYER);
			Enemy::GetInst()->ChooseControlTank();
			SetDestroy(true);
		}
	}
	if (other->m_Tag == "Enemy")
	{
		if (Team == TEAM::PLAYER)
		{
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position), "Effect");
			Camera::GetInst()->m_CannonBall = false;
			Camera::GetInst()->Follow(nullptr);
			if (Team == TEAM::PLAYER)
				GameMgr::GetInst()->SetTurn(TURN::ENEMY);
			else if (Team == TEAM::ENEMY)
				GameMgr::GetInst()->SetTurn(TURN::PLAYER);
			Player::GetInst()->m_Move = 100;
			Enemy::GetInst()->ChooseControlTank();
			SetDestroy(true);
		}
	}
}

void CannonBall::SetRotation()
{
	m_Distance = m_NextPos - m_Position;

	float rad = atan2(m_Distance.x, m_Distance.y);

	m_Rotation = -rad + D3DXToRadian(90);
}

void CannonBall::SetVertex()
{
	Vertex1.x = m_Position.x +((m_Size.x - 15) / 2) * cos(m_Rotation) - ((m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex1.y = m_Position.y + ((m_Size.x - 15) / 2) * sin(m_Rotation) + ((m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex2.x = m_Position.x + ((-m_Size.x - 15) / 2) * cos(m_Rotation) - ((m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex2.y = m_Position.y + ((-m_Size.x - 15) / 2) * sin(m_Rotation) + ((m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex3.x = m_Position.x + ((-m_Size.x - 15) / 2) * cos(m_Rotation) - ((-m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex3.y = m_Position.y + ((-m_Size.x - 15) / 2) * sin(m_Rotation) + ((-m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex4.x = m_Position.x + ((m_Size.x - 15) / 2) * cos(m_Rotation) - ((-m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex4.y = m_Position.y + ((m_Size.x - 15) / 2) * sin(m_Rotation) + ((-m_Size.y - 15) / 2) * cos(m_Rotation);
}
