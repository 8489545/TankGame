#include "stdafx.h"
#include "CannonBall.h"

CannonBall::CannonBall(float power, float rot, Vec2 Pos)
{
	m_CannonBall = Sprite::Create(L"Painting/Object/CannonBall.png");
	m_CannonBall->SetParent(this);

	m_Pos = Pos;
	m_Power = power / 2 + 5;
	m_Rotation = rot;
	m_StartingRotation = rot;
	GR = 0.4f;
	t = 0;
}

CannonBall::~CannonBall()
{
}

void CannonBall::Update(float deltaTime, float time)
{
	ObjMgr->CollisionCheak(this, "Tile");
	Camera::GetInst()->Follow(this);
	m_Position.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x ;
	m_Position.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;
	t++;

	m_NextPos.x = (m_Power * cos(m_StartingRotation)) * t + m_Pos.x;
	m_NextPos.y = (m_Power * sin(m_StartingRotation)) * t + GR / 2 * t * t + m_Pos.y;

	SetRotation();
	SetVertex();
}

void CannonBall::Render()
{
	m_CannonBall->Render();
}

void CannonBall::OnCollision(Object* other)
{
	printf("%f", other->m_SlopeRot);
	if (other->m_Tag == "Tile")
	{
		if (CollisionMgr::GetInst()->LineToLineCollide(Vertex1, Vertex2, other->m_LinePos1, other->m_LinePos2))
		{
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