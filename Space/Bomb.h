#pragma once
class Bomb : public Object
{
	Sprite* m_Bomb;
public:
	Bomb(Vec2 Pos, TEAM team);
	~Bomb();

	Vec2 Vertex1, Vertex2, Vertex3, Vertex4;

	float vy;

	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);

	void SetVertex();
};

