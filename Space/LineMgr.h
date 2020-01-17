#pragma once
class LineMgr : public Singleton<LineMgr>
{
	LPD3DXLINE m_pLine;
	D3DXCOLOR m_Color;
public:
	LineMgr();
	~LineMgr();


	LPD3DXLINE GetLine()
	{
		return m_pLine;
	}

	void Init(float width, bool antialias);
	void DrawLine(Vec2* vec,int size);
	void SetColor(D3DXCOLOR color);

};

