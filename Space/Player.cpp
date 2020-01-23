#include "stdafx.h"
#include "Player.h"

Player::Player()
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                {
	m_MainPanel = Sprite::Create(L"Painting/UI/MainPanel.png");
	m_MainPanel->SetPosition(1920 / 2, 939);

	ObjMgr->AddObject(m_MainPanel, "UI");

	m_MoveBar = Sprite::Create(L"Painting/UI/MoveBar.png");
	m_MoveBar->SetPosition(725, 1010);
	m_PowerBar = Sprite::Create(L"Painting/UI/PowerBar.png");
	m_PowerBar->SetPosition(725, 925);
	m_HpBar = Sprite::Create(L"Painting/UI/HpBar.png");
	m_HpBar->SetPosition(1226, 960);

	m_GroundRot = Sprite::Create(L"Painting/UI/GroundRot.png");
	m_GroundRot->SetPosition(125, 970);
	m_BarrelRot = Sprite::Create(L"Painting/UI/BarrelRot.png");
	m_BarrelRot->SetPosition(125, 970);
	m_MaxRot = Sprite::Create(L"Painting/UI/LimitRot.png");
	m_MaxRot->SetPosition(125, 970);
	m_MinRot = Sprite::Create(L"Painting/UI/LimitRot.png");
	m_MinRot->SetPosition(125, 970);

	ObjMgr->AddObject(m_MoveBar, "UI");
	ObjMgr->AddObject(m_PowerBar, "UI");
	ObjMgr->AddObject(m_HpBar, "UI");

	ObjMgr->AddObject(m_GroundRot, "UI");
	ObjMgr->AddObject(m_BarrelRot, "UI");
	ObjMgr->AddObject(m_MaxRot, "UI");
	ObjMgr->AddObject(m_MinRot, "UI");

	m_RotationText = new TextMgr();
	m_RotationText->Init(32, false, true, "Impact");
	m_RotationText->SetColor(255, 0, 0, 0);

	m_MapLine = new LineMgr();
	m_MapLine->Init(2, true);
	m_MapLine->SetColor(D3DXCOLOR(255, 0, 0, 255));

	m_Power = 0;
	m_MaxPower = 100;

	m_Move = 99999;
	m_MaxMove = 99999;

	m_Hp = 100;
	m_MaxHp = 100;


	m_MainPanel->m_Layer = 1;
	m_PowerBar->m_Layer = 2;
	m_MoveBar->m_Layer = 2;
	m_HpBar->m_Layer = 2;

	m_GroundRot->m_Layer = 4;
	m_BarrelRot->m_Layer = 3;
	m_MaxRot->m_Layer = 2;
	m_MinRot->m_Layer = 2;
}

Player::~Player()
{

}

void Player::Update(float deltaTime, float time)
{
	if (m_Power >= m_MaxPower)
		m_Power = m_MaxPower;

	m_GroundRot->m_Rotation = m_Ground;
	m_BarrelRot->m_Rotation = m_Barrel;
	m_MaxRot->m_Rotation = m_Max;
	m_MinRot->m_Rotation = m_Min;

}

void Player::DrawMap()
{
	int TileNum = 0;
	std::vector<Object*> Tile;
	Vec2 MapPos = Vec2(1400, 850);
	Vec2 MiniMapSize = Vec2(536,196);
	for (auto& iter : ObjMgr->m_Objects)
	{
		if (iter->m_Tag == "Tile")
		{
			Tile.push_back(iter);
		}
	}
	TileNum = Tile.size();
	float MapSize = (TileNum -1) * 300.f;

	Vec2* Map = new Vec2[TileNum];

	for (int i = 0; i < Tile.size(); ++i)
	{
		Map[i].x = Tile.at(i)->m_Position.x * (100 - abs((MiniMapSize.x - MapSize) / MapSize * 100)) / 100 + MapPos.x;
		Map[i].y = (Tile.at(i)->m_Position.y * 15 / 100) + MapPos.y;
	}

	m_MapLine->DrawLine(Map, TileNum);
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

	//////////

	m_HpGage = m_HpBar->m_Size.x / m_MaxHp;

	int Hp = m_MaxHp - m_Hp;

	SetRect(&m_HpBar->m_Collision, m_HpBar->m_Position.x - m_HpBar->m_Size.x / 2, m_HpBar->m_Position.y - m_HpBar->m_Size.y / 2,
		m_HpBar->m_Position.x + m_HpBar->m_Size.x / 2, m_HpBar->m_Position.y + m_HpBar->m_Size.y / 2);

	m_HpBar->m_Rect.right = m_HpBar->m_Size.x - (Hp * m_HpGage);

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_RotationText->print(std::to_string(abs((int)(D3DXToDegree(m_Barrel)))), 100,800);
	Renderer::GetInst()->GetSprite()->End();

	DrawMap();
}
