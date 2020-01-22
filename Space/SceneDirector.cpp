#include "stdafx.h"
#include "SceneDirector.h"


SceneDirector::SceneDirector()
{
}


SceneDirector::~SceneDirector()
{
}

void SceneDirector::ChangeScene(Object* newScene)
{
	if (m_CurrentScene)
	{
		SafeDelete(m_CurrentScene);
	}

	m_CurrentScene = newScene;
}

void SceneDirector::Update(float deltaTime, float time)
{
	Input::GetInst()->Update();
	Camera::GetInst()->Update(deltaTime, time);


	ObjMgr->Update(deltaTime,time);
	
	if (m_CurrentScene)
		m_CurrentScene->Update(deltaTime,time);
	if (GameMgr::GetInst()->m_isPlayer)
		Player::GetInst()->Update(deltaTime, time);

}

void SceneDirector::Render()
{
	if (m_CurrentScene)
		m_CurrentScene->Render();
	ObjMgr->Render();
	if (GameMgr::GetInst()->m_isPlayer)
		Player::GetInst()->Render();
}
