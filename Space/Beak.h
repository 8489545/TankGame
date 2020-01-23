#pragma once
class Beak : public Object
{
	Sprite* m_BG;
	Sprite* m_SKY;
	Sprite* m_Cannons[3];
public:
	Beak();
	~Beak();

	Vec2 m_GroundPos;
	Vec2 m_WaterPos;

	void Update(float deltaTime, float Time);
	void Render();
};

