#pragma once
class MainScene : public Object
{
	Sprite* m_BackGround;

	Sprite* m_Title1;
	Sprite* m_Title2;
	Sprite* m_Title3;
	Sprite* m_Title4;
	Sprite* m_Title5;

	Sprite* m_Cannon;

	Animation* m_Boom;

	Sprite* m_StartButton;

	Sprite* m_Door1;
	Sprite* m_Door2;

public:
	MainScene();
	~MainScene();

	float Term;
	bool SceneChange;


	void Update(float deltaTime, float time);
	void Render();


	void Fail(Object* obj);
};

