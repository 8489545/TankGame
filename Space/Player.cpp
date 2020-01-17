#include "stdafx.h"
#include "Player.h"

Player::Player()
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                {
	m_MainPanel = Sprite::Create(L"Painting/UI/MainPanel.png");
	m_MainPanel->SetPosition(1920 / 2, 970);

	ObjMgr->AddObject(m_MainPanel, "UI");

	m_MoveBar = Sprite::Create(L"Painting/UI/MoveBar.png");
	m_MoveBar->SetPosition(725, 1010);
	m_PowerBar = Sprite::Create(L"Painting/UI/PowerBar.png");
	m_PowerBar->SetPosition(725, 925);

	ObjMgr->AddObject(m_MoveBar, "UI");
	ObjMgr->AddObject(m_PowerBar, "UI");


	m_Power = 0;
	m_MaxPower = 100;

	m_Move = 99999;
	m_MaxMove = 99999;


	m_MainPanel->m_Layer = 1;
	m_PowerBar->m_Layer = 2;
	m_MoveBar->m_Layer = 2;
}

Player::~Player()
{

}

void Player::Update(float deltaTime, float time)
{
	if (m_Power >= m_MaxPower)
		m_Power = m_MaxPower;
}

void Player::Render()
{
	m_PowerGage = m_PowerBar->m_Size.x / m_MaxPower;

	int power = m_MaxPower - m_Power;

	SetRect(&m_PowerBar->m_Collision, m_PowerBar->m_Position.x - m_PowerBar->m_Size.x / 2, m_PowerBar->m_Position.y - m_PowerBar->m_Size.y / 2,
		m_PowerBar->m_Position.x + m_PowerBar->m_Size.x / 2, m_PowerBar->m_Position.y + m_PowerBar->m_Size.y / 2);

	m_PowerBar->m_Rect.right = m_PowerBar->m_Size.x - (power * m_PowerGage);
	
	//////////

	m_MoveGage = m_MoveBar->m_Size.x / m_MaxMove;

	int move = m_MaxMove - m_Move;

	SetRect(&m_MoveBar->m_Collision, m_MoveBar->m_Position.x - m_MoveBar->m_Size.x / 2, m_MoveBar->m_Position.y - m_MoveBar->m_Size.y / 2,
		m_MoveBar->m_Position.x + m_MoveBar->m_Size.x / 2, m_MoveBar->m_Position.y + m_MoveBar->m_Size.y / 2);

	m_MoveBar->m_Rect.right = m_MoveBar->m_Size.x - (move * m_MoveGage);
}
