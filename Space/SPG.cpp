#include "stdafx.h"
#include "SPG.h"
#include"CannonBall.h"

SPG::SPG(Vec2 pos, TEAM team)
{
	m_SPG = new Animation();
	m_SPG->AddContinueFrame(L"Painting/Object/Tank/SPG", 1, 4);
	m_SPG->Init(7, true);
	m_SPG->SetParent(this);
	m_Position = pos;

	m_Barrel = Sprite::Create(L"Painting/Object/Tank/Barrel.png");

	m_FrontFootPos = Sprite::Create(L"Painting/Object/Tank/TankCol.png");
	m_BackFootPos = Sprite::Create(L"Painting/Object/Tank/TankCol.png");

	m_Active = Sprite::Create(L"Painting/Object/Tank/Active.png");

	m_FrontFootPos->m_Visible = false;
	m_BackFootPos->m_Visible = false;

	m_isGround = false;
	m_Speed = 300;

	m_MaxRot = D3DXToRadian(-90);
	m_MinRot = 0;

	m_CorrectionValue = Vec2(50, -35);
	m_Barrel->m_CenterPos.x = -70;

	INPUT->ButtonDown(false);

	m_LockOn = false;

	Team = team;
	m_Hp = 100;

}

SPG::~SPG()
{
}

void SPG::Update(float deltaTime, float Time)
{
	ObjMgr->CollisionCheak(this, "Tile");
	ObjMgr->CollisionCheak(this, "CannonBall");

	if(Team == TEAM::PLAYER)
		LockOn();
	Gravity();
	SetObjectPos();

	

	if (m_LockOn && GameMgr::GetInst()->GetTurn() == TURN::PLAYER)
	{
		Player::GetInst()->m_MaxHp = 100;
		Player::GetInst()->m_Hp = m_Hp;
		if(!Camera::GetInst()->m_CannonBall)
			Camera::GetInst()->Follow(this);
		else
			Camera::GetInst()->Follow(nullptr);
		Move();
		Shot();
		BarrelAngleContorl();
		SetFootPos();
		CheakMove();
		SetVar();
	}
	else
	{
		Camera::GetInst()->Follow(nullptr);
		m_Active->m_Visible = false;
	}
	if (m_Hp <= 0)
	{
		ObjMgr->AddObject(new EffectMgr(L"Painting/Effect/explosion/", 1, 10, m_Position), "Effect");
		Player::GetInst()->Tanks -= 1;
		ObjMgr->RemoveObject(this);
	}
	m_SPG->Update(deltaTime, Time);
}

void SPG::Render()
{
	m_SPG->Render();
	m_Barrel->Render();
	m_FrontFootPos->Render();
	m_BackFootPos->Render();
	m_Active->Render();
}

void SPG::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
	{
		GroundCol(other);
	}
	if (other->m_Tag == "Tile" && other->Team == TEAM::ENEMY)
	{
		m_Hp -= 30;
	}
}

void SPG::LockOn()
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(this) && INPUT->GetButtonDown())
	{
		if (!m_LockOn)
			m_LockOn = true;
		else if (m_LockOn)
			m_LockOn = false;
		INPUT->ButtonDown(false);
	}

	if (m_LockOn)
	{
		for (auto& iter : ObjMgr->m_Objects)
		{
			if (iter != this)
			{
				if (iter->m_LockOn == true)
					iter->m_LockOn = false;
			}
		}
	}
}

void SPG::Move()
{
	A = m_Position;
	B.x = sin(m_Rotation + D3DXToRadian(90));
	B.y = cos(m_Rotation + D3DXToRadian(90));

	C = A - B;

	D3DXVec2Normalize(&C, &B);
	m_FrontWater = false;
	m_BackWater = false;

	for (auto& iter : ObjMgr->m_Objects)
	{
		RECT rc;
		if (iter->m_isWater)
		{
			if (IntersectRect(&rc, &m_FrontFootPos->m_Collision, &iter->m_Collision))
			{
				m_FrontWater = true;
			}
			if (IntersectRect(&rc, &m_BackFootPos->m_Collision, &iter->m_Collision))
			{
				m_BackWater = true;
			}
		}
	}
	if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && Player::GetInst()->m_Move > 0 && !m_FrontWater)
	{
		Translate(C.x * m_Speed * dt, -C.y * m_Speed * dt);
		Player::GetInst()->m_Move -= 1.f;
	}
	if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && Player::GetInst()->m_Move > 0 && !m_BackWater)
	{
		Translate(-C.x * m_Speed * dt, C.y * m_Speed * dt);
		Player::GetInst()->m_Move -= 1.f;
	}
}

void SPG::Shot()
{
	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS)
	{
		Player::GetInst()->m_Power++;
	}
	if (INPUT->GetKey(VK_SPACE) == KeyState::UP && !Camera::GetInst()->m_CannonBall)
	{
		if(Player::GetInst()->m_Power > 0)
			ObjMgr->AddObject(new CannonBall(Player::GetInst()->m_Power, m_Barrel->m_Rotation, m_BarrelEnd, Team), "CannonBall");
		Player::GetInst()->m_Power = 0;
	}
}

void SPG::BarrelAngleContorl()
{

	m_MaxRot = m_Rotation;
	m_MinRot = m_Rotation + D3DXToRadian(-90);

	Player::GetInst()->m_Ground = m_Rotation;
	Player::GetInst()->m_Barrel = m_Barrel->m_Rotation;
	Player::GetInst()->m_Max = m_MaxRot;
	Player::GetInst()->m_Min = m_MinRot;


	if (m_Barrel->m_Rotation > m_MaxRot)
		m_Barrel->m_Rotation = m_MaxRot;

	if (m_Barrel->m_Rotation < m_MinRot)
		m_Barrel->m_Rotation = m_MinRot;

	if (INPUT->GetKey(VK_UP) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode)
	{
		m_Barrel->m_Rotation -= D3DXToRadian(1);
	}
	if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode)
	{
		m_Barrel->m_Rotation += D3DXToRadian(1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	}

	m_BarrelEnd.x = m_Barrel->m_Position.x - 50 + cos(m_Barrel->m_Rotation) * m_Barrel->m_Size.x;
	m_BarrelEnd.y = m_Barrel->m_Position.y + sin(m_Barrel->m_Rotation) * m_Barrel->m_Size.x;
}

void SPG::Gravity()
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

void SPG::GroundCol(Object* other)
{
	m_isGround = true;
	if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS && INPUT->GetKey(VK_LEFT) != KeyState::PRESS)
	{
		Object* obj = nullptr;
		RECT rc;
		for (auto& iter : ObjMgr->m_Objects)
		{
			if(IntersectRect(&rc, &iter->m_Collision, &m_FrontFootPos->m_Collision))
			{
				obj = iter;
			}
		}

		if (obj != nullptr)
		{
			float NowDis = DotToLineDistance(m_FrontFootPos->m_Position, obj->m_LinePos1, obj->m_LinePos2);
			if (IntersectRect(&rc, &obj->m_Collision, &m_FrontFootPos->m_Collision))
			{
				if (NowDis >= 5 && obj->m_SlopeRot < 0)
				{
					m_Rotation -= D3DXToRadian(1);

					if (m_Rotation - D3DXToRadian(obj->m_SlopeRot) < 0.1f)
						m_Rotation = D3DXToRadian(obj->m_SlopeRot);
				}
				else if (NowDis >= 5 && obj->m_SlopeRot > 0)
				{
					m_Rotation += D3DXToRadian(0.3);

					if (abs(m_Rotation - D3DXToRadian(obj->m_SlopeRot)) < 0.1f)
						m_Rotation = D3DXToRadian(obj->m_SlopeRot);
				}
				else if (NowDis >= 5 && obj->m_SlopeRot == 0)
				{
					m_Rotation -= D3DXToRadian(1);

					if (abs(m_Rotation) < 0.1f)
						m_Rotation = 0;
				}
			}
		}
		else
		{
			if (m_Rotation < 0)
				m_Rotation += D3DXToRadian(1);

			if (abs(m_Rotation) < 0.1f)
				m_Rotation = 0;
		}
	}

	if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS && INPUT->GetKey(VK_RIGHT) != KeyState::PRESS)
	{
		Object* obj = nullptr;
		RECT rc;
		for (auto& iter : ObjMgr->m_Objects)
		{
			if (IntersectRect(&rc, &iter->m_Collision, &m_BackFootPos->m_Collision))
			{
				obj = iter;
			}
		}

		if (obj != nullptr)
		{
			float NowDis = DotToLineDistance(m_BackFootPos->m_Position, obj->m_LinePos1, obj->m_LinePos2);
			if (IntersectRect(&rc, &obj->m_Collision, &m_BackFootPos->m_Collision))
			{
				if (NowDis >= 5 && obj->m_SlopeRot < 0)
				{
					m_Rotation -= D3DXToRadian(1);

					if (m_Rotation - D3DXToRadian(obj->m_SlopeRot) < 0.1f)
						m_Rotation = D3DXToRadian(obj->m_SlopeRot);
				}
				else if (NowDis >= 5 && obj->m_SlopeRot > 0)
				{
					m_Rotation += D3DXToRadian(1);

					if (abs(m_Rotation - D3DXToRadian(obj->m_SlopeRot)) < 0.1f)
						m_Rotation = D3DXToRadian(obj->m_SlopeRot);
				}
				else if (NowDis >= 5 && obj->m_SlopeRot == 0)
				{
					m_Rotation += D3DXToRadian(1);

					if (abs(m_Rotation) < 0.1f)
						m_Rotation = 0;
				}
			}
		}
		else
		{
			if (m_Rotation > 0)
				m_Rotation -= D3DXToRadian(1);

			if (abs(m_Rotation) < 0.1f)
				m_Rotation = 0;
		}
	}
}

void SPG::SetFootPos()
{
	m_FrontFootPos->m_Position.x = m_Position.x + (m_Size.x / 2) * cos(m_Rotation) - (m_Size.y / 2) * sin(m_Rotation);
	m_FrontFootPos->m_Position.y = m_Position.y + (m_Size.x / 2) * sin(m_Rotation) + (m_Size.y / 2) * cos(m_Rotation);

	m_BackFootPos->m_Position.x = m_Position.x + (-m_Size.x / 2) * cos(m_Rotation) - (m_Size.y / 2) * sin(m_Rotation);
	m_BackFootPos->m_Position.y = m_Position.y + (-m_Size.x / 2) * sin(m_Rotation) + (m_Size.y / 2) * cos(m_Rotation);
}

void SPG::CheakMove()
{
	if (m_PrevPos != m_Position)
		m_isMove = true;
	else
		m_isMove = false;
}

void SPG::SetObjectPos()
{
	m_Barrel->m_Position.x = m_Position.x - 85 + cos(m_Rotation) * m_Size.x;
	m_Barrel->m_Position.y = m_Position.y - 35;
	m_Active->m_Position = m_Position;
	m_Active->m_Rotation = m_Rotation;
}

void SPG::SetVar()
{
	m_isGround = false;
	m_PrevRotation = m_Rotation;
	m_PrevPos = m_Position;
	Player::GetInst()->m_NowPos = m_Position;
	m_Active->m_Visible = true;
}

float SPG::DotToLineDistance(Vec2 Dot, Vec2 Line1, Vec2 Line2)
{
	float a = Line1.y - Line2.y;
	float b = Line2.x - Line1.x;
	float c = (Line1.x * Line2.y) - (Line2.x * Line1.y);

	float dis;
	return dis = abs(a * Dot.x + b * Dot.y + c) / sqrt(pow(a, 2) + pow(b, 2));
}
