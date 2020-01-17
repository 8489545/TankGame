#pragma once
class Texture;
class Sprite : public Object
{
	LPD3DXSPRITE m_pSp;
	Texture* m_Texture;

public:
	RECT m_Rect;

public:
	Sprite();
	~Sprite();

public:
	bool Init(std::wstring fileName);

public:
	RECT GetRect() { return m_Rect; }

	static Sprite* Create(std::wstring fileName);
	void Render() override;

public:
	int A, R, G, B;
};