#include "stdafx.h"
#include "WinScene.h"
#include"StageSelect.h"

WinScene::WinScene()
{
	m_BG = Sprite::Create(L"Painting/BG/Win.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	m_Button = Sprite::Create(L"Painting/UI/Cheak.png");
	m_Button->SetParent(this);
	m_Button->SetPosition(1250, 850);
}

WinScene::~WinScene()
{
}

void WinScene::Update(float deltaTime, float time)
{
	Camera::GetInst()->Init();
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button) && INPUT->GetButtonDown())
	{
		exit(0);
	}
}

void WinScene::Render()
{
	m_BG->Render();
	m_Button->Render();
}
