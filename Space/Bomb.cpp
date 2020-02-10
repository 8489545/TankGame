#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(Vec2 Pos, TEAM team)
{
	m_Bomb = Sprite::Create(L"Painting/Object/Bomb.png");
	m_Bomb->SetParent(this);

	m_Position = Pos;

	vy = 0;

	Team = team;
}

Bomb::~Bomb()
{
}

void Bomb::Update(float deltaTime, float time)
{
	Camera::GetInst()->m_CannonBall = true;
	ObjMgr->CollisionCheak(this, "Tile");
	ObjMgr->CollisionCheak(this, "Tank");
	ObjMgr->CollisionCheak(this, "Enemy");
	Camera::GetInst()->Follow(this);

	vy += 9.8f * dt;
	m_Position.y += vy;

	SetVertex();
}

void Bomb::Render()
{
	m_Bomb->Render();
}

void Bomb::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
	{
		if (CollisionMgr::GetInst()->LineToLineCollide(Vertex1, Vertex2, other->m_LinePos1, other->m_LinePos2)
			|| CollisionMgr::GetInst()->LineToLineCollide(Vertex2, Vertex3, other->m_LinePos1, other->m_LinePos2))
		{
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position), "Effect");
			Camera::GetInst()->m_CannonBall = false;
			Camera::GetInst()->Follow(nullptr);
			if (Team == TEAM::PLAYER)
				GameMgr::GetInst()->SetTurn(TURN::ENEMY);
			else if (Team == TEAM::ENEMY)
				GameMgr::GetInst()->SetTurn(TURN::PLAYER);
			Player::GetInst()->m_Move = 100;
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

void Bomb::SetVertex()
{
	Vertex1.x = m_Position.x + ((m_Size.x - 15) / 2) * cos(m_Rotation) - ((m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex1.y = m_Position.y + ((m_Size.x - 15) / 2) * sin(m_Rotation) + ((m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex2.x = m_Position.x + ((-m_Size.x - 15) / 2) * cos(m_Rotation) - ((m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex2.y = m_Position.y + ((-m_Size.x - 15) / 2) * sin(m_Rotation) + ((m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex3.x = m_Position.x + ((-m_Size.x - 15) / 2) * cos(m_Rotation) - ((-m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex3.y = m_Position.y + ((-m_Size.x - 15) / 2) * sin(m_Rotation) + ((-m_Size.y - 15) / 2) * cos(m_Rotation);

	Vertex4.x = m_Position.x + ((m_Size.x - 15) / 2) * cos(m_Rotation) - ((-m_Size.y - 15) / 2) * sin(m_Rotation);
	Vertex4.y = m_Position.y + ((m_Size.x - 15) / 2) * sin(m_Rotation) + ((-m_Size.y - 15) / 2) * cos(m_Rotation);
}
