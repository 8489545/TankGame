#pragma once

class StageSelect : public Object
{
	Sprite* m_BG;
	Sprite* m_Door1;
	Sprite* m_Door2;

	Sprite* m_IntroBeakRyung;
	Sprite* m_IntroDaeChung;
	Sprite* m_IntroSoChung;
	Sprite* m_IntroUDo;
	Sprite* m_IntroYeonPyeong;

	Sprite* m_BCol;
	Sprite* m_DCol;
	Sprite* m_SCol;
	Sprite* m_UCol;
	Sprite* m_YCol;

	Sprite* m_Start;


	Sprite* m_IntroPanel;
public:
	 
	StageSelect();
	~StageSelect();

	STAGE m_Stage;

	void Update(float deltaTime, float Time);
	void Render();
};

