#pragma once
class SPG : public Object
{
	Animation* m_SPG;
	Sprite* m_Barrel;
	Sprite* m_FrontFootPos;
	Sprite* m_BackFootPos;
	Sprite* m_Col;
	TextMgr* m_Text;
	LineMgr* line;

public:
	SPG(Vec2 pos);
	~SPG();

	Vec2 m_CorrectionValue;

	bool m_isGround;
	bool m_isLaunching;
	bool m_isMove;
	float m_GroundHeight;
	float m_Speed;
	float m_PrevRotation;
	float m_MaxRot;
	float m_MinRot;
	float m_FrontRot;
	float m_BackRot;
	float m_PrevDis;
	float m_NearDis;

	Vec2 A, B, C;
	Vec2 m_BarrelEnd;
	Vec2 m_PrevPos;
	Vec2 m_MidPos;

	void Update(float deltaTime,float Time);
	void Render();
	void OnCollision(Object* other);

	void Move();
	void Shot();
	void BarrelAngleContorl();
	void Gravity();
	void GroundCol(Object* other);
	void SetFootPos();
	void CheakMove();
	float DotToLineDistance(Vec2 Dot, Vec2 Line1, Vec2 Line2);
};

