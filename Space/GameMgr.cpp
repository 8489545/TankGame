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

void GameMgr::CreateEnemy()
{
	Enemy::GetInst();
	m_isEnemy = true;
}

void GameMgr::ChangeTurn()
{
	if (m_Turn == TURN::PLAYER)
	{
		m_Turn = TURN::ENEMY;
	}
	else if (m_Turn == TURN::ENEMY)
	{
		m_Turn = TURN::PLAYER;
	}
}

void GameMgr::SetTurn(TURN turn)
{
	m_Turn = turn;
}

TURN GameMgr::GetTurn()
{
	return m_Turn;
}
