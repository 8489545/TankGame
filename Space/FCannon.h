#pragma once
class FCannon : public Object
{
	Animation* m_Cannon;
	Sprite* m_Barrel;
public:
	FCannon(Vec2 Pos, TEAM team, int num);
	~FCannon();

	TEAM Team;
	Vec2 m_BarrelEnd;
	
	int m_CannonNum;
	bool m_isGround;

	void Gravity();
	void SetEndPos();

	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);
};

