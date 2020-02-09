#pragma once
class Player : public Singleton<Player>
{
public:
	Sprite* m_MainPanel;

	Sprite* m_MoveBar;
	Sprite* m_PowerBar;
	Sprite* m_HpBar;

	Sprite* m_GroundRot;
	Sprite* m_BarrelRot;
	Sprite* m_MinRot;
	Sprite* m_MaxRot;

	Sprite* m_NowObj;

	Sprite* m_EnemyObj[5];

	TextMgr* m_RotationText;
	LineMgr* m_MapLine;

	std::vector<CANNON> m_Cannons;

	Player();
	~Player();

	float m_Power;
	float m_MaxPower;
	float m_Move;
	float m_MaxMove;
	float m_Hp;
	float m_MaxHp;
	float m_Ground;
	float m_Barrel;
	float m_Min;
	float m_Max;

	Vec2 m_RotationCenter;
	Vec2 m_NowPos;

	float m_PowerGage;
	float m_MoveGage;
	float m_HpGage;

	void Update(float deltaTime, float time);
	void Render();
	void DrawMap();
	void SpawnCannon(int num,Vec2 Pos,Vec2 WaterPos);
	void SetEnemyPos(int num, Vec2 Pos);
};

