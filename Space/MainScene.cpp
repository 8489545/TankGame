#include"stdafx.h"
#include "MainScene.h"
#include"StageSelect.h"


MainScene::MainScene()
{
	m_BackGround = Sprite::Create(L"Painting/BG/Main.png");
	m_BackGround->SetParent(this);

	m_BackGround->SetPosition(1920 / 2, 1080 / 2);

	m_Title1 = Sprite::Create(L"Painting/UI/Title1.png");
	m_Title1->SetParent(this);

	m_Title2 = Sprite::Create(L"Painting/UI/Title2.png");
	m_Title2->SetParent(this);

	m_Title3 = Sprite::Create(L"Painting/UI/Title3.png");
	m_Title3->SetParent(this);

	m_Title4 = Sprite::Create(L"Painting/UI/Title4.png");
	m_Title4->SetParent(this);

	m_Title5 = Sprite::Create(L"Painting/UI/Title5.png");
	m_Title5->SetParent(this);

	m_Cannon = Sprite::Create(L"Painting/Object/Cannon.png");
	m_Cannon->SetParent(this);
	m_Cannon->SetPosition(-500,770);

	m_StartButton = Sprite::Create(L"Painting/UI/Start.png");
	m_StartButton->SetParent(this);
	m_StartButton->SetPosition(2000, 631);

	m_Door1 = Sprite::Create(L"Painting/Object/OpenDoor.png");
	m_Door1->SetParent(this);
	m_Door1->SetPosition(1920 / 2, -500);

	m_Door2 = Sprite::Create(L"Painting/Object/OpenDoor2.png");
	m_Door2->SetParent(this);
	m_Door2->SetPosition(1920 / 2, 1580);

	m_Title1->SetPosition(624 - m_Title1->m_Size.x, -500);
	m_Title2->SetPosition(848 - m_Title1->m_Size.x, -700);
	m_Title3->SetPosition(1072 - m_Title1->m_Size.x, -900);
	m_Title4->SetPosition(1296 - m_Title1->m_Size.x, -1100);
	m_Title5->SetPosition(1520 - m_Title1->m_Size.x, -1300);


	Term = 0.5f;

}

MainScene::~MainScene()
{
}

void MainScene::Update(float deltaTime, float time)
{
	Fail(m_Title1);
	Fail(m_Title2);
	Fail(m_Title3);
	Fail(m_Title4);
	Fail(m_Title5);

	if (m_Title5->m_Position.y == 200.f)
	{
		Term -= deltaTime;

		if (m_StartButton->m_Position.x > 1575)
			m_StartButton->m_Position.x -= 1500 * deltaTime;

		if (m_StartButton->m_Position.x <= 1575)
			m_StartButton->m_Position.x = 1575;

		if (m_Cannon->m_Position.x < 200)
			m_Cannon->m_Position.x += 1500 * deltaTime;

		if (m_Cannon->m_Position.x >= 200)
			m_Cannon->m_Position.x = 200;
	}

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_StartButton) && INPUT->GetButtonDown())
	{
		SceneChange = true;
	}
	if (SceneChange)
	{
		if (m_Door1->m_Position.y <= 250)
		{
			m_Door1->m_Position.y += 1200 * deltaTime;
			m_Door2->m_Position.y -= 1200 * deltaTime;
		}
		else
		{
			SceneDirector::GetInst()->ChangeScene(new StageSelect());
		}

	}
	
}

void MainScene::Render()
{
	m_BackGround->Render();

	m_Title1->Render();
	m_Title2->Render();
	m_Title3->Render();
	m_Title4->Render();
	m_Title5->Render();
	if (m_Title5->m_Position.y == 200.f)
	{
		m_Cannon->Render();

		m_StartButton->Render();
	}

	m_Door1->Render();
	m_Door2->Render();
}

void MainScene::Fail(Object* obj)
{
	if(obj->m_Position.y < 200.f)
	{
		obj->m_Position.y += 1200.f * dt;
	}
	else
	{
		obj->m_Position.y = 200.f;
	}
}


