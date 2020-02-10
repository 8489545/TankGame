#pragma once
struct Cannon
{
	int CannonNum;
	Vec2 CannonPos;
};
class Enemy : public Singleton<Enemy>
{
public:
	Enemy();
	~Enemy();

	std::vector<Cannon*> m_Cannons;

	int m_CurrentTank;

	void AddCannon(int num,Vec2 pos);
	void SpawnCannon();

	void Update(float deltaTime, float time);
	void Render();
};

