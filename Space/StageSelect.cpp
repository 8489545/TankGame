#include "stdafx.h"
#include "StageSelect.h"
#include"Beak.h"
#include"CannonMgr.h"

StageSelect::StageSelect()
{
	m_BG = Sprite::Create(L"Painting/BG/Select.png");
	m_BG->SetParent(this);
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	m_Door1 = Sprite::Create(L"Painting/Object/OpenDoor.png");
	m_Door1->SetParent(this);
	m_Door1->SetPosition(1920 / 2, 250);

	m_Door2 = Sprite::Create(L"Painting/Object/OpenDoor2.png");
	m_Door2->SetParent(this);
	m_Door2->SetPosition(1920 / 2, 1580 - 770);

	m_IntroPanel = Sprite::Create(L"Painting/UI/IntroPanel.png");
	m_IntroPanel->SetParent(this);
	m_IntroPanel->SetPosition(1920 / 2 + 150, 1080 / 2);



	m_IntroBeakRyung = Sprite::Create(L"Painting/Object/BeakRyungDo.png");
	m_IntroBeakRyung->SetParent(this);
	m_IntroBeakRyung->SetPosition(1660, 230);

	m_BCol = Sprite::Create(L"Painting/UI/Collision.png");
	m_BCol->SetParent(this);
	m_BCol->SetPosition(505, 414);


	m_Start = Sprite::Create(L"Painting/UI/Go.png");
	m_Start->SetParent(this);
	m_Start->SetPosition(1760,900);

}

StageSelect::~StageSelect()
{
}

void StageSelect::Update(float deltaTime, float Time)
{

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_BCol) && INPUT->GetButtonDown())
	{
		m_Stage = STAGE::BEAK;
	}
	GameMgr::GetInst()->NextStage(m_Stage);

	if (m_Door1->m_Position.y >= -500)
	{
		m_Door1->m_Position.y -= 1200 * deltaTime;
		m_Door2->m_Position.y += 1200 * deltaTime;
	}

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Start) && INPUT->GetButtonDown())
	{
		SceneDirector::GetInst()->ChangeScene(new CannonMgr());
		INPUT->ButtonDown(false);
	}

}

void StageSelect::Render()
{
	m_BG->Render();
	m_IntroPanel->Render();


	switch (m_Stage)
	{
	case STAGE::BEAK:
		m_IntroBeakRyung->Render();
		break;
	default:
		break;
	}
	m_Start->Render();


	m_Door1->Render();
	m_Door2->Render();
}
