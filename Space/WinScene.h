#pragma once
class WinScene : public Object
{
	Sprite* m_BG;
	Sprite* m_Button;
public:
	WinScene(STAGE stage);
	~WinScene();

	void Update(float deltaTime,float time);
	void Render();
};

