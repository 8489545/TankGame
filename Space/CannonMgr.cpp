#include "stdafx.h"
#include "CannonMgr.h"

CannonMgr::CannonMgr()
{
	m_CannonPanel = Sprite::Create(L"Painting/UI/CannonPanel.png");
	m_CannonPanel->SetParent(this);
	m_CannonPanel->SetPosition(1920 / 2, 1080 / 2);

	m_SPG = Sprite::Create(L"Painting/Object/SPG.png");
	m_SPG->SetParent(this);
	m_SPG->SetPosition(500, 1080 / 2);

	m_FCannon = Sprite::Create(L"Painting/Object/FCannon.png");
	m_FCannon->SetParent(this);
	m_FCannon->SetPosition(800, 1080 / 2);

	m_MRL = Sprite::Create(L"Painting/Object/MRL.png");
	m_MRL->SetParent(this);
	m_MRL->SetPosition(1100, 1080 / 2);

	m_MTRAP = Sprite::Create(L"Painting/Object/MTRAP.png");
	m_MTRAP->SetParent(this);
	m_MTRAP->SetPosition(1400, 1080 / 2);

	m_GameStart = Sprite::Create(L"Painting/UI/GameStart.png");
	m_GameStart->SetParent(this);
	m_GameStart->SetPosition(1920 / 2,910);
	
	m_CannonNum = 0;
}

CannonMgr::~CannonMgr()
{
}

void CannonMgr::AddCannon(CANNON cannon)
{
	Vec2 UIPos;
	UIPos.x = 728 + 173 * m_CannonNum;
	UIPos.y = 310;

	PlayerCannon.push_back(cannon);
	m_CannonNum++;

	switch (cannon)
	{
	case CANNON::SPG:
		m_Cannons[m_CannonNum] = Sprite::Create(L"Painting/UI/SPGSelect.png");
		m_Cannons[m_CannonNum]->SetParent(this);
		m_Cannons[m_CannonNum]->m_Position = UIPos;
		break;
	case CANNON::FCANNON:
		m_Cannons[m_CannonNum] = Sprite::Create(L"Painting/UI/FCannonSelect.png");
		m_Cannons[m_CannonNum]->SetParent(this);
		m_Cannons[m_CannonNum]->m_Position = UIPos;
		break;
	case CANNON::MRL:
		m_Cannons[m_CannonNum] = Sprite::Create(L"Painting/UI/MRLSelect.png");
		m_Cannons[m_CannonNum]->SetParent(this);
		m_Cannons[m_CannonNum]->m_Position = UIPos;
		break;
	case CANNON::MTRAP:
		m_Cannons[m_CannonNum] = Sprite::Create(L"Painting/UI/MTRAPSelect.png");
		m_Cannons[m_CannonNum]->SetParent(this);
		m_Cannons[m_CannonNum]->m_Position = UIPos;
		break;
	case CANNON::NONE:
		break;
	default:
		break;
	}
}

void CannonMgr::Delete()
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Cannons[m_CannonNum]) && INPUT->GetButtonDown())
	{	
		PlayerCannon.pop_back();
		m_CannonNum--;
		ObjMgr->RemoveObject(m_Cannons[m_CannonNum]);
		INPUT->ButtonDown(false);
	}
}

void CannonMgr::Update(float deltaTime, float Time)
{
	if (m_CannonNum < 3)
	{
		if (CollisionMgr::GetInst()->MouseWithBoxSize(m_SPG) && INPUT->GetButtonDown())
		{
			AddCannon(CANNON::SPG);
			INPUT->ButtonDown(false);
		}
		if (CollisionMgr::GetInst()->MouseWithBoxSize(m_FCannon) && INPUT->GetButtonDown())
		{
			AddCannon(CANNON::FCANNON);
			INPUT->ButtonDown(false);
		}
		if (CollisionMgr::GetInst()->MouseWithBoxSize(m_MRL) && INPUT->GetButtonDown())
		{
			AddCannon(CANNON::MRL);
			INPUT->ButtonDown(false);
		}
		if (CollisionMgr::GetInst()->MouseWithBoxSize(m_MTRAP) && INPUT->GetButtonDown())
		{
			AddCannon(CANNON::MTRAP);
			INPUT->ButtonDown(false);
		}
	}
	if(m_CannonNum >= 1)
		Delete();

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_GameStart) && INPUT->GetButtonDown() && m_CannonNum == 3)
	{
		GameMgr::GetInst()->m_CannonVec = PlayerCannon;
		GameMgr::GetInst()->ChangeNextStage();
		GameMgr::GetInst()->CreatePlayer();
		ObjMgr->RemoveObject(this);
	}
}

void CannonMgr::Render()
{
	m_CannonPanel->Render();
	m_SPG->Render();
	m_MRL->Render();
	m_FCannon->Render();
	m_MTRAP->Render();
	
	if (m_CannonNum == 3)
		m_GameStart->Render();

	if (m_CannonNum > 0)
	{
		for (int i = 1; i <= m_CannonNum; i++)
		{
			m_Cannons[i]->Render();
		}
	}
}