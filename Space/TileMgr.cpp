#include "stdafx.h"
#include "TileMgr.h"

TileMgr::TileMgr()
{
	m_Key = 0;
	m_CurPos = Vec2(0, 0);
}

TileMgr::~TileMgr()
{
}

void TileMgr::Update(float delatTime, float time)
{
}

void TileMgr::Render()
{
}

void TileMgr::InsertToPalette(std::wstring filename)
{
	Tile* tile = new Tile();

	tile->FileName = filename;
	tile->TileNum = m_Key;

	m_Tiles.push_back(tile);

	m_Key++;
}

void TileMgr::SetTilePos(Vec2 pos)
{
	m_CurPos = pos;
}

void TileMgr::DrawMap(int mapdata[],int mapsize)
{
	for (int i = 0; i < mapsize;i++)
	{
		Sprite* Tile = new Sprite();
		Tile = Sprite::Create(L"Painting/BG/Tile/" + m_Tiles.at(abs(mapdata[i]))->FileName + L".png");
		Tile->m_Position = m_CurPos;
		Tile->m_Tag = "Tile";

		Tile->m_LinePos1.x = Tile->m_Position.x - Tile->m_Size.x / 2;
		Tile->m_LinePos1.y = Tile->m_Position.y - Tile->m_Size.y / 2;

		Tile->m_LinePos2.x = Tile->m_LinePos1.x + Tile->m_Size.x;
		Tile->m_LinePos2.y = Tile->m_LinePos1.y;

		if (m_Tiles.at(abs(mapdata[i]))->FileName.find(L"Slope") == 0)
		{
			if (mapdata[i] > 0)
			{
				Tile->m_SlopeRot = -31.5f - floor(-31.5f / 360.f) * 360.f;
				Tile->m_LinePos1.y += 183.f;
			}
			else
			{
				Tile->m_SlopeRot = 31.5f;
				Tile->m_LinePos2.y += 183.f;
			}
		}
		ObjMgr->AddObject(Tile, "Tile");


		if (Tile->m_SlopeRot == 31.5f && i + 1 < mapsize && mapdata[i + 1] == 0)
		{
			m_CurPos.y += 184.f;
		}

		if (i + 1 < mapsize && mapdata[i + 1] < 0)
		{
			if(m_Tiles.at(abs(mapdata[i]))->FileName.find(L"Slope") == 0)
				m_CurPos.y += 184.f;
		}
		else
		{
			if (i + 1 < mapsize && m_Tiles.at(abs(mapdata[i + 1]))->FileName.find(L"Slope") == 0)
				m_CurPos.y -= 184.f;
		}

		m_CurPos.x += 300.f;
	}
}

void TileMgr::DeletePalette()
{
	for (auto& iter : ObjMgr->m_Objects)
	{
		if (iter->m_Tag == "Tile")
		{
			iter->SetDestroy(true);
		}
	}
	m_Tiles.clear();
}
