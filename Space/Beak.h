#pragma once
class Beak : public Object
{
	Sprite* m_BG;
	Sprite* m_SKY;
	Sprite* m_Cannons[3];
public:
	Beak();
	~Beak();

	void Update(float deltaTime, float Time);
	void Render();
};

