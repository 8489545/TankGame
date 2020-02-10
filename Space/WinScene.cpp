#include "stdafx.h"
#include "WinScene.h"
#include"StageSelect.h"

WinScene::WinScene(STAGE stage)
{
	m_BG = Sprite::Create(L"Painting/BG/Win.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	m_Button = Sprite::Create(L"Painting/UI/Cheak.png");
	m_Button->SetParent(this);
	m_Button->SetPosition(1250, 850);
	switch (stage)
	{
	case STAGE::BEAK:
		GameMgr::GetInst()->m_BeakClear = true;
		break;
	case STAGE::DAE:
		GameMgr::GetInst()->m_DaeClear = true;
		break;
	case STAGE::SO:
		GameMgr::GetInst()->m_SoClear = true;
		break;
	case STAGE::U:
		GameMgr::GetInst()->m_UClear = true;
		break;
	case STAGE::YEON:
		GameMgr::GetInst()->m_YeonClear = true;
		break;
	case STAGE::NONE:
		break;
	default:
		break;
	}
}

WinScene::~WinScene()
{
}

void WinScene::Update(float deltaTime, float time)
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button) && INPUT->GetButtonDown())
	{
		SceneDirector::GetInst()->ChangeScene(new StageSelect());
	}
}

void WinScene::Render()
{
	m_BG->Render();
	m_Button->Render();
}
