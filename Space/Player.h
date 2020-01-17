#pragma once
class Player : public Singleton<Player>
{
public:
	Sprite* m_MainPanel;

	Sprite* m_MoveBar;
	Sprite* m_PowerBar;

	Player();
	~Player();

	void Update(float deltaTime, float time);
	void Render();

	float m_Power;
	float m_MaxPower;
	float m_Move;
	float m_MaxMove;

	Vec2 m_RotationCenter;

	float m_PowerGage;
	float m_MoveGage;
};
