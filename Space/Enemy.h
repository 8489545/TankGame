#pragma once
class Enemy : public Singleton<Enemy>
{
public:
	Enemy();
	~Enemy();

	void Update(float deltaTime, float time);
	void Render();
};

