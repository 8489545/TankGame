#include "stdafx.h"
#include "EffectMgr.h"

EffectMgr::EffectMgr(std::wstring filename,  int start, int end ,Vec2 Pos)
{
	Effect = new Animation();
	Effect->AddContinueFrame(filename, start, end);
	Effect->Init(7, true);
	Effect->SetParent(this);
	Effect->m_Position = Pos;
}

EffectMgr::~EffectMgr()
{
}

void EffectMgr::Update(float deltaTime, float time)
{
}

void EffectMgr::Render()
{
}

void EffectMgr::OnCollision(Object* other)
{
}
