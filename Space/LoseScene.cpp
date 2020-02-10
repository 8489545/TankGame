#include "stdafx.h"
#include "LoseScene.h"
#include"StageSelect.h"

LoseScene::LoseScene()
{
	m_BG = Sprite::Create(L"Painting/BG/Lose.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	m_Button = Sprite::Create(L"Painting/UI/Cheak.png");
	m_Button->SetParent(this);
	m_Button->SetPosition(1250, 850);
}

LoseScene::~LoseScene()
{
}

void LoseScene::Update(float deltaTime, float time)
{
	Camera::GetInst()->Init();
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button) && INPUT->GetButtonDown())
	{
		exit(0);
	}
}

void LoseScene::Render()
{
	m_BG->Render();
	m_Button->Render();
}
