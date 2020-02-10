#include "stdafx.h"
#include "Beak.h"
#include"FCannon.h"

Beak::Beak()
{
	m_BG = Sprite::Create(L"Painting/BG/BG.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2,1800 / 2);

	m_GroundPos = Vec2(300, 300);
	m_WaterPos = Vec2(2500, 300);

	ObjMgr->AddObject(m_BG, "BG");

	for (int i = 0; i < 3; ++i)
	{
		Player::GetInst()->SpawnCannon(i, Vec2(m_GroundPos.x + (i * 100), m_GroundPos.y),
			Vec2(m_WaterPos.x + (i * 100), m_WaterPos.y));
	}
	GameMgr::GetInst()->CreateEnemy();
	GameMgr::GetInst()->SetTurn(TURN::PLAYER);

	Enemy::GetInst()->AddCannon(0, Vec2(7000, 500));
	Enemy::GetInst()->AddCannon(1, Vec2(7800, 0));
	Enemy::GetInst()->AddCannon(2, Vec2(8100, 0));
	Enemy::GetInst()->AddCannon(3, Vec2(8600, 0));

	Enemy::GetInst()->SpawnCannon();

	TileMgr::GetInst()->InsertToPalette(L"FlatTile");
	TileMgr::GetInst()->InsertToPalette(L"Slope30");
	TileMgr::GetInst()->InsertToPalette(L"Slope30R");
	TileMgr::GetInst()->InsertToPalette(L"Water");
	TileMgr::GetInst()->SetTilePos(Vec2(-1000 / 2,2200 / 2));

	int map[] = {0,0,0,0,0,1,1,0,-2,0,3,3,3,3,3,3,3,3,1,0,-2,-2,0,0,0,0,1,1,0,0,0,0,-2,0,0,0,0};

	Camera::GetInst()->m_MaxX = (sizeof(map) / sizeof(int) * 300) - 1000 - 1920;
	Camera::GetInst()->m_MinX = -650;

	Camera::GetInst()->m_MaxY = 300;
	Camera::GetInst()->m_MinY = -300;

	TileMgr::GetInst()->DrawMap(map,sizeof(map) / sizeof(int));

}

Beak::~Beak()
{
}

void Beak::Update(float deltaTime, float Time)
{
	m_BG->m_Position.x = Camera::GetInst()->m_X + 1920 / 2;
	m_BG->m_Position.y = Camera::GetInst()->m_Y + 1080 / 2;
}

void Beak::Render()
{

}
