#include "stdafx.h"
#include "Beak.h"
#include"SPG.h"

Beak::Beak()
{
	m_BG = Sprite::Create(L"Painting/BG/Beak.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2,1800 / 2);

	m_SKY = Sprite::Create(L"Painting/BG/BeakSky.png");
	m_SKY->SetParent(this);
	m_SKY->SetPosition(1920 / 2,1080 / 2);

	ObjMgr->AddObject(m_SKY, "BG");
	//ObjMgr->AddObject(m_BG, "BG");
	
	ObjMgr->AddObject(new SPG(Vec2(0, 0)), "Tank");

	TileMgr::GetInst()->InsertToPalette(L"FlatTile");
	TileMgr::GetInst()->InsertToPalette(L"Slope30");
	TileMgr::GetInst()->InsertToPalette(L"Slope30R");
	TileMgr::GetInst()->InsertToPalette(L"Water");
	TileMgr::GetInst()->SetTilePos(Vec2(-1000 / 2,2200 / 2));

	int map[] = { 0,0,0,0,1,0,-2,0,1,0,0,0,-2,-2,0,0,0,1,1,1,1,0,0,-2,-2,0,0,1,0,-2,0,3,3,3,3,3,3,3,3,0,0,0,0,1,1,1,0,0,0,0};

	TileMgr::GetInst()->DrawMap(map,sizeof(map) / sizeof(int));
}

Beak::~Beak()
{
}

void Beak::Update(float deltaTime, float Time)
{
}

void Beak::Render()
{

}
