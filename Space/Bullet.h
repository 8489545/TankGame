#pragma once
class Bullet : public Object
{
	Sprite* m_Bullet;
public:
	Bullet(Vec2 Pos,float Rotation);
	~Bullet();

	Vec2 A, B, C;
	Vec2 m_Vertex;
	float m_BulletLife;

	void Update(float deltaTime,float time);
	void Render();
	void OnCollision(Object* other);
};

