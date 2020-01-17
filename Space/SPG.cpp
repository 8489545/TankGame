#include "stdafx.h"
#include "SPG.h"
#include"CannonBall.h"

SPG::SPG(Vec2 pos)
{
	m_SPG = new Animation();
	m_SPG->AddContinueFrame(L"Painting/Object/Tank/SPG", 1, 4);
	m_SPG->Init(7, true);
	m_SPG->SetParent(this);
	m_SPG->m_Position = pos;
	SetPosition(300, 300);

	m_Barrel = Sprite::Create(L"Painting/Object/Tank/Barrel.png");

	m_FrontFootPos = Sprite::Create(L"Painting/Object/Tank/TankCol.png");
	m_BackFootPos = Sprite::Create(L"Painting/Object/Tank/TankCol.png");

	m_isGround = false;
	m_Speed = 300.f;

	m_Text = new TextMgr();
	m_Text->Init(32, true, false, "Arial");

	m_MaxRot = D3DXToRadian(-90);
	m_MinRot = 0;

	m_CorrectionValue = Vec2(50, -35);
	m_Barrel->m_CenterPos.x = -70;

	INPUT->ButtonDown(false);
}

SPG::~SPG()
{
}

void SPG::Update(float deltaTime, float Time)
{
	Camera::GetInst()->Follow(this);
	ObjMgr->CollisionCheak(this, "Tile");
	Gravity();
	Move();
	Shot();
	BarrelAngleContorl();
	SetFootPos();
	CheakMove();

	m_isGround = false;
	m_PrevRotation = m_Rotation;
	m_PrevPos = m_Position;
	m_SPG->Update(deltaTime, Time);
}

void SPG::Render()
{
	m_SPG->Render();
	m_Barrel->Render();
	m_FrontFootPos->Render();
	m_BackFootPos->Render();

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_Text->print(std::to_string(INPUT->GetMousePos().x) + "  " + std::to_string(INPUT->GetMousePos().y), 0, 0);
	Renderer::GetInst()->GetSprite()->End();
}

void SPG::OnCollision(Object* other)
{
	if (other->m_Tag == "Tile")
		GroundCol(other);
}

void SPG::Move()
{
	A = m_Position;
	B.x = sin(m_Rotation + D3DXToRadian(90));
	B.y = cos(m_Rotation + D3DXToRadian(90));

	C = A - B;

	D3DXVec2Normalize(&C, &B);

	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS)
		int i = 0;

	if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && Player::GetInst()->m_Move > 0)
	{
		Translate(C.x * m_Speed * dt, -C.y * m_Speed * dt);
		Player::GetInst()->m_Move -= 1.f;
	}
	if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && Player::GetInst()->m_Move > 0)
	{
		Translate(-C.x * m_Speed * dt, C.y * m_Speed * dt);
		Player::GetInst()->m_Move -= 1.f;
	}
}

void SPG::Shot()
{
	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS)
	{
		if (m_isLaunching)
		{
			Player::GetInst()->m_Power = 0;
			m_isLaunching = false;
		}
		Player::GetInst()->m_Power++;
	}
	if (INPUT->GetKey(VK_SPACE) == KeyState::UP)
		m_isLaunching = true;

	if (INPUT->GetButtonDown() && m_isGround && Player::GetInst()->m_Power >= 1)
	{
		ObjMgr->AddObject(new CannonBall(Player::GetInst()->m_Power, m_Barrel->m_Rotation, m_BarrelEnd), "CannonBall");
		Player::GetInst()->m_Power = 0;
		INPUT->ButtonDown(false);
	}
}

void SPG::BarrelAngleContorl()
{
	m_Barrel->m_Position.x = m_Position.x;
	m_Barrel->m_Position.y = m_Position.y;

	if (INPUT->GetKey(VK_UP) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && m_Barrel->m_Rotation >= m_MaxRot)
	{
		m_Barrel->m_Rotation -= D3DXToRadian(1);
	}
	if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS && m_isGround && !Camera::GetInst()->m_MovingMode && m_Barrel->m_Rotation <= m_MinRot)
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
		m_Barrel->m_Position.y += vy;
	}
	else
		vy = 0;
}

void SPG::GroundCol(Object* other)
{

	printf("F %f B %f\n", m_FrontRot, m_BackRot);

	m_isGround = true;
	if (m_isMove)
	{
		for (auto& iter : ObjMgr->m_Objects)
		{
			if (iter->m_Tag == "Tile")
			{
				RECT rc;
				if (IntersectRect(&rc, &m_FrontFootPos->m_Collision, &iter->m_Collision))
				{
					m_FrontRot = iter->m_SlopeRot;
				}
			}
			else
				m_FrontRot;
		}

		for (auto& iter : ObjMgr->m_Objects)
		{
			if (iter->m_Tag == "Tile")
			{
				RECT rc;
				if (IntersectRect(&rc, &m_BackFootPos->m_Collision, &iter->m_Collision))
				{
					m_BackRot = iter->m_SlopeRot;
				}
			}
			else
				m_BackRot;
		}

		if (m_FrontRot == m_BackRot)
		{
			m_Rotation = D3DXToRadian(m_FrontRot);
		}
		else
		{
			if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS)
			{
				if (m_FrontRot > m_BackRot && m_FrontRot > 90)
				{
					m_Barrel->m_Rotation -= D3DXToRadian(1);
					m_Rotation -= D3DXToRadian(1);

					m_MinRot -= D3DXToRadian(1);
					m_MaxRot -= D3DXToRadian(1);
				}
				else if(m_FrontRot > m_BackRot&& m_FrontRot < 90)
				{
					m_Barrel->m_Rotation += D3DXToRadian(0.5f);
					m_Rotation += D3DXToRadian(0.5f);

					m_MinRot += D3DXToRadian(0.5f);
					m_MaxRot += D3DXToRadian(0.5f);
				}
				else if (m_FrontRot < m_BackRot && m_BackRot > 90 )
				{
					m_Barrel->m_Rotation += D3DXToRadian(0.5f);
					m_Rotation += D3DXToRadian(0.5f);

					m_MinRot += D3DXToRadian(0.5f);
					m_MaxRot += D3DXToRadian(0.5f);
				}
				else if (m_FrontRot < m_BackRot && m_BackRot < 90)
				{
					m_Barrel->m_Rotation -= D3DXToRadian(1);
					m_Rotation -= D3DXToRadian(1);

					m_MinRot -= D3DXToRadian(1);
					m_MaxRot -= D3DXToRadian(1);
				}
			}
			if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS)
			{
				if (m_FrontRot > m_BackRot && m_FrontRot > 90)
				{
					m_Barrel->m_Rotation += D3DXToRadian(1);
					m_Rotation += D3DXToRadian(1);

					m_MinRot += D3DXToRadian(1);
					m_MaxRot += D3DXToRadian(1);
				}
				else if (m_FrontRot > m_BackRot && m_FrontRot < 90)
				{
					m_Barrel->m_Rotation -= D3DXToRadian(0.5f);
					m_Rotation -= D3DXToRadian(0.5f);

					m_MinRot -= D3DXToRadian(0.5f);
					m_MaxRot -= D3DXToRadian(0.5f);
				}
				else if (m_FrontRot < m_BackRot && m_BackRot > 90)
				{
					m_Barrel->m_Rotation -= D3DXToRadian(0.5f);
					m_Rotation -= D3DXToRadian(0.5f);

					m_MinRot -= D3DXToRadian(0.5f);
					m_MaxRot -= D3DXToRadian(0.5f);
				}
				else if (m_FrontRot < m_BackRot && m_BackRot < 90)
				{
					m_Barrel->m_Rotation += D3DXToRadian(1);
					m_Rotation += D3DXToRadian(1);

					m_MinRot += D3DXToRadian(1);
					m_MaxRot += D3DXToRadian(1);
				}
			}
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