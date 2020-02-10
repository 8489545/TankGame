#pragma once
class WinScene : public Object
{
	Sprite* m_BG;
	Sprite* m_Button;
public:
	WinScene();
	~WinScene();

	void Update(float deltaTime,float time);
	void Render();
};

