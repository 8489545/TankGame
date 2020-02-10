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
	int m_ControlTankNum;

	void AddCannon(int num,Vec2 pos);
	void SpawnCannon();
	void ChooseControlTank();

	void Update(float deltaTime, float time);
	void Render();
};

