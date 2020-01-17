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
	m_MovingMode = false;
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
	if (obj != nullptr && !m_MovingMode)
	{
		m_X = obj->m_Position.x - App::GetInst()->m_Width / 2;
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
	Translate();
	Zoom();

	if (m_Rotation >= 360)
		m_Rotation = 0;
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
