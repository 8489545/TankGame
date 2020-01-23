#pragma once
class Object
{
public:
	LPDIRECT3DDEVICE9 m_pDev;
	Object* m_Parent;

	Matrix m_wMat;
	Vec2 m_Position;
	Vec2 m_Scale;
	Vec2 m_Size;
	float m_Rotation;
	float m_SlopeRot;

	bool m_Destroy;
	bool m_MouseCol;
	bool m_LockOn;
	RECT m_Collision;

	bool m_Visible;
	bool m_isWater;

	int m_Layer;
	std::string m_Tag;

	Vec2 m_RotationCenter;
	Vec2 m_CenterPos;
	Vec2 m_ScaleCenter;

	Vec2 m_LinePos1;
	Vec2 m_LinePos2;


public:
	Object();
	virtual ~Object();


protected:
	Matrix GetMatrix();

public:
	virtual void Update(float deltaTime, float time);
	virtual void Render();
	virtual void OnCollision(Object* other);

public:
	void Translate(float x, float y);
	void SetScale(float x, float y);
	void SetPosition(float x, float y);
	void Rotate(float r);
	void SetDestroy(bool destroy) { m_Destroy = destroy; }
	void SetParent(Object* parent);
	void SetTag(const std::string tag);
public:
	bool GetDestroy() { return m_Destroy; }
};