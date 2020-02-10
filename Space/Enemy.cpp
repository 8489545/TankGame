#include "stdafx.h"
#include "Enemy.h"
#include"FCannon.h"

Enemy::Enemy()
{
	m_CurrentTank = 0;
}

Enemy::~Enemy()
{
}

void Enemy::AddCannon(int num, Vec2 pos)
{
	Cannon* cannon = new Cannon();
	cannon->CannonNum = num;
	cannon->CannonPos = pos;
	m_Cannons.push_back(cannon);

	m_CurrentTank++;
}

void Enemy::SpawnCannon()
{
	for (int i = 0; i < m_CurrentTank; i++)
	{
		ObjMgr->AddObject(new FCannon(m_Cannons.at(i)->CannonPos,TEAM::ENEMY, m_Cannons.at(i)->CannonNum), "Enemy");
	}
}

void Enemy::ChooseControlTank()
{
	m_ControlTankNum = rand() % m_CurrentTank;

	if(m_Cannons.at(m_CurrentTank) == nullptr)
		m_ControlTankNum = rand() % m_CurrentTank;
}

void Enemy::Update(float deltaTime, float time)
{
}

void Enemy::Render()
{
}
