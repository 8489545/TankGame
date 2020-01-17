#include"stdafx.h"
#include "IntroScene.h"
#include"MainScene.h"

IntroScene::IntroScene()
{
	m_IntroCut1 = Sprite::Create(L"Painting/BG/Intro1.png");
	m_IntroCut1->SetParent(this);
	m_IntroCut1->SetPosition(1920 / 2, 1080 / 2);

	m_IntroCut2 = Sprite::Create(L"Painting/BG/Intro2.png");
	m_IntroCut2->SetParent(this);
	m_IntroCut2->SetPosition(1920 / 2, 1080 / 2);

	m_IntroCut3 = Sprite::Create(L"Painting/BG/Intro3.png");
	m_IntroCut3->SetParent(this);
	m_IntroCut3->SetPosition(1920 / 2, 1080 / 2);

	m_IntroCut4 = Sprite::Create(L"Painting/BG/Intro4.png");
	m_IntroCut4->SetParent(this);
	m_IntroCut4->SetPosition(1920 / 2, 1080 / 2);

	m_Skip = Sprite::Create(L"Painting/UI/ArrowNormal.png");
	m_Skip->SetParent(this);
	m_Skip->SetPosition(2000,2030);

	m_IntroCut4->A = 0;
	m_IntroCut3->A = 0;
	m_IntroCut2->A = 0;

	m_Count = 0;
	m_Cut = 1;
}

IntroScene::~IntroScene()
{

}

void IntroScene::Update(float deltaTime, float time)
{
	m_Count += deltaTime;

	if (m_Count >= 1.f)
	{
		switch (m_Cut)
		{
		case 1:
			m_IntroCut2->A += 5;
			if (m_IntroCut2->A == 255)
			{
				m_Cut = 2;
				m_Count = 0.f;
			}
			break;
		case 2:
			m_IntroCut3->A += 5;
			m_IntroCut4->A = 0;
			if (m_IntroCut3->A == 255)
			{
				m_Cut = 3;
				m_Count = 0.f;
			}
		case 3:
			m_IntroCut4->A += 5;
			if (m_IntroCut4->A == 255)
			{
				m_Cut = 0;
				m_Count = 0.f;

				m_Skip->SetPosition(1730, 930);
			}
			break;
		default:
			break;
		}
	}
	printf("cut %d\n", m_Cut);
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Skip) && INPUT->GetButtonDown())
		SceneDirector::GetInst()->ChangeScene(new MainScene());

	if (INPUT->GetKey(VK_SPACE) == KeyState::DOWN)
	{
		SceneDirector::GetInst()->ChangeScene(new MainScene());
	}
}

void IntroScene::Render()
{
	m_IntroCut1->Render();
	m_IntroCut2->Render();
	m_IntroCut3->Render();
	m_IntroCut4->Render();

	if (m_Cut == 0)
		m_Skip->Render();
}
