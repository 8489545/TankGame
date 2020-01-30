#pragma once
class CannonBall : public Object
{
public:
	Sprite* m_CannonBall;
	Sprite* m_Missile;

	CannonBall(float power,float rot,Vec2 Pos);
	~CannonBall();

	float GR;
	int t;
	float m_Power;
	float m_StartingRotation;

	Vec2 m_Pos;
	Vec2 m_NextPos;
	Vec2 m_Distance;

	Vec2 Vertex1, Vertex2, Vertex3, Vertex4;

	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);

	void SetRotation();
	void SetVertex();
};

