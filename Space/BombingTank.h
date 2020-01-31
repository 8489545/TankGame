#pragma once
class BombingTank : public Object
{
	Animation* m_BombingTank;
	Sprite* m_Barrel;
	Sprite* m_FrontFootPos;
	Sprite* m_BackFootPos;
	Sprite* m_Active;

public:
	BombingTank(Vec2 pos);
	~BombingTank();

	Vec2 m_CorrectionValue;

	bool m_isGround;
	bool m_isMove;
	bool m_FrontWater;
	bool m_BackWater;
	bool m_CannonBall;
	float m_GroundHeight;
	float m_Speed;
	float m_PrevRotation;
	float m_MaxRot;
	float m_MinRot;
	float m_FrontRot;
	float m_BackRot;

	Vec2 A, B, C;
	Vec2 m_BarrelEnd;
	Vec2 m_PrevPos;

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);

	void LockOn();
	void Move();
	void Shot();
	void BarrelAngleContorl();
	void Gravity();
	void GroundCol(Object* other);
	void SetFootPos();
	void CheakMove();
	void SetObjectPos();
	void SetVar();
	float DotToLineDistance(Vec2 Dot, Vec2 Line1, Vec2 Line2);
};

