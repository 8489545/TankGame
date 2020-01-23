#include "stdafx.h"
#include "GameMgr.h"
#include"CannonMgr.h"
#include"Beak.h"
#include"Player.h"

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}

void GameMgr::NextStage(STAGE stage)
{
	m_Next = stage;
}

void GameMgr::ChangeNextStage()
{
	switch (m_Next)
	{
	case STAGE::BEAK:
		SceneDirector::GetInst()->ChangeScene(new Beak());
		break;
	case STAGE::DAE:
		break;
	case STAGE::SO:
		break;
	case STAGE::U:
		break;
	case STAGE::YEON:
		break;
	case STAGE::NONE:
		break;
	default:
		break;
	}
}

void GameMgr::CreatePlayer()
{
	Player::GetInst();
	Player::GetInst()->m_Cannons = m_CannonVec;
	m_isPlayer = true;
}
