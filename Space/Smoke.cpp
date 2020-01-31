#include "stdafx.h"
#include "Smoke.h"

Smoke::Smoke(float power, float rot, Vec2 Pos)
{
	m_Smoke = Sprite::Create(L"Painting/Object/Smoke.png");
	m_Smoke->SetParent(this);

	m_Pos = Pos;
	m_Power = power / 3 + 5;
	m_Rotation = rot;
	m_StartingRotation = rot;
	GR = 0.2f;
	t = 0;
}

Smoke::~Smoke()
{
}

void Smoke::Update(float deltaTime, float time)
{
	Camera::GetInst()->m_CannonBall = true;
	ObjMgr->CollisionCheak(this, "Tile");
	Camera::GetInst()->Follow(this);
	m_Position.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x;
	m_Position.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;
	t++;

	SetRotation();
	SetVertex();

	if (m_Position.x >= Camera::GetInst()->m_MaxX + 1920 || m_Position.x <= Camera::GetInst()->m_MinX)
		SetDestroy(true);
}

void Smoke::Render()
{
	m_Smoke->Render();
}

void Smoke::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
	{
		if (CollisionMgr::GetInst()->LineToLineCollide(Vertex1, Vertex2, other->m_LinePos1, other->m_LinePos2)
			|| CollisionMgr::GetInst()->LineToLineCollide(Vertex2, Vertex3, other->m_LinePos1, other->m_LinePos2)
			|| CollisionMgr::GetInst()->LineToLineCollide(Vertex3, Vertex4, other->m_LinePos1, other->m_LinePos2)
			|| CollisionMgr::GetInst()->LineToLineCollide(Vertex4, Vertex1, other->m_LinePos1, other->m_LinePos2))
		{
			ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/Smoke/", 1, 20, Vec2(m_Position.x,m_Position.y - 100)), "Smoke");
			Camera::GetInst()->m_CannonBall = false;
			SetDestroy(true);
		}
	}
}

void Smoke::SetRotation()
{
	m_Rotation += D3DXToRadian(1);
}

void Smoke::SetVertex()
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
