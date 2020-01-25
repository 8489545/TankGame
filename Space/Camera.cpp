#include"stdafx.h"
#include "Camera.h"
Camera::Camera()
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Init()
{
	m_Rotation = 0;
	m_X = 0;
	m_Y = 0;
	m_sX = 1.f;
	m_sY = 1.f;
	m_MaxX = 0;
	m_MinX = 0;
	m_MaxY = 0;
	m_MinY = 0;
	m_MovingMode = false;
	m_CannonBall = false;
}

void Camera::Translate()
{
	if (INPUT->GetKey(VK_INSERT) == KeyState::DOWN)
	{
		if (m_MovingMode)
			m_MovingMode = false;
		else
			m_MovingMode = true;
	}
	if (m_MovingMode)
	{
		if (INPUT->GetKey(VK_UP) == KeyState::PRESS)
		{
			m_Y -= 600 * dt;
		}
		if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS)
		{
			m_Y += 600 * dt;
		}
		if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS)
		{
			m_X -= 600 * dt;
		}
		if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS)
		{
			m_X += 600 * dt;
		}
	}
}

void Camera::Follow(Object* obj)
{
	if (obj != nullptr && !m_MovingMode && (obj->m_Position.x != 0 && obj->m_Position.y != 0))
	{
		if(obj->m_Position.x - App::GetInst()->m_Width / 2 < m_MaxX && obj->m_Position.x - App::GetInst()->m_Width / 2 > m_MinX)
			m_X = obj->m_Position.x - App::GetInst()->m_Width / 2;
		if(obj->m_Position.y - App::GetInst()->m_Height / 2 < m_MaxY && obj->m_Position.y - App::GetInst()->m_Height / 2 > m_MinY)
			m_Y = obj->m_Position.y - App::GetInst()->m_Height / 2;
	}
}

void Camera::Zoom()
{
	if (INPUT->GetKey('O') == KeyState::PRESS)
	{
		m_sX += 0.5f * dt;
		m_sY += 0.5f * dt;
	}
	if (INPUT->GetKey('P') == KeyState::PRESS)
	{
		m_sX -= 0.5f * dt;
		m_sY -= 0.5f * dt;
	}
	if (INPUT->GetKey('Z') == KeyState::PRESS)
	{
		m_sX = 1.f;
		m_sY = 1.f;
	}
}


void Camera::Update(float deltaTime, float time)
{
	printf("%f %f\n", m_X, m_Y);
	Translate();
	//Zoom();

	if (m_Rotation >= 360)
		m_Rotation = 0;

	if (m_X > m_MaxX)
		m_X = m_MaxX;

	if (m_Y > m_MaxY)
		m_Y = m_MaxY;

	if (m_X < m_MinX)
		m_X = m_MinX;

	if (m_Y < m_MinY)
		m_Y = m_MinY;
}

void Camera::Render()
{
	D3DXMatrixRotationZ(&mRot, D3DXToRadian(m_Rotation));
	D3DXMatrixTranslation(&mTrans, -m_X, -m_Y, 1.f);
	D3DXMatrixScaling(&mScale, m_sX, m_sY, 1.f);

	// 카메라 
	//mScale* mRot* mTrans
	mWorld = mScale * mRot * mTrans;
}
