#pragma once
#include<DirectXMath.h>
using namespace DirectX;
class Camera : public Singleton<Camera>
{
private:
	Matrix mRot;
	Matrix mTrans;
	Matrix mScale;
	Matrix mWorld;
public:
	Camera();
	~Camera();


	float m_Rotation;
	float m_X, m_Y;
	float m_sX, m_sY;
	float m_Timer;
	bool m_MovingMode;

	float m_MaxX, m_MaxY;
	float m_MinX, m_MinY;


	Matrix GetWorld()
	{
		return mWorld;
	}

	void Init();
	void Translate();
	void Follow(Object* obj);
	void Zoom();
	void Update(float deltaTime, float time);
	void Render();
};
