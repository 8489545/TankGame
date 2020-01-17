#include"stdafx.h"
#include "LineMgr.h"

LineMgr::LineMgr()
{
	
}

LineMgr::~LineMgr()
{
}

void LineMgr::Init(float width, bool antialias)
{
	D3DXCreateLine(Renderer::GetInst()->GetDevice(), &m_pLine);

	m_pLine->SetWidth(width);
	m_pLine->SetAntialias(antialias);
	m_pLine->SetPattern(0xffffffff);
}

void LineMgr::DrawLine(Vec2* vec,int size)
{
	m_pLine->Begin();
	m_pLine->Draw(vec, size, m_Color);
	m_pLine->End();
}

void LineMgr::SetColor(D3DXCOLOR color)
{
	m_Color = color;
}
 