#pragma once
class LoseScene : public Object
{
	Sprite* m_BG;
	Sprite* m_Button;
public:
	LoseScene();
	~LoseScene();

	void Update(float deltaTime, float time);
	void Render();
};

