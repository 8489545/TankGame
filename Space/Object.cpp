
#include "stdafx.h"
#include "Object.h"


Object::Object() :
	m_pDev(Renderer::GetInst()->GetDevice())
	, m_Position(0.f, 0.f)
	, m_Rotation(0.f)
	, m_Scale(1.f, 1.f)
	, m_Destroy(0)
	, m_Parent(0)
	, m_Visible(true)
	, m_Layer(0)
	, m_Size(0.f, 0.f)
	, m_Tag("UnNamed")
	, m_MouseCol(false)
	, m_LockOn(false)
	, m_RotationCenter(0.f,0.f)
	, m_SlopeRot(0.f)
	, m_CenterPos(0.f,0.f)
	, m_LinePos1(0.f,0.f)
	, m_LinePos2(0.f,0.f)
	, m_isWater(false)
	, m_Hp(0)
{
	m_pDev->AddRef();
	D3DXMatrixIdentity(&m_wMat);
}


Object::~Object()
{
}

Matrix Object::GetMatrix()
{

	if (m_Tag != "UI")
	{
		m_RotationCenter.x = -Camera::GetInst()->m_X + m_CenterPos.x;
		m_RotationCenter.y = -Camera::GetInst()->m_Y + m_CenterPos.y;

		m_ScaleCenter.x = -Camera::GetInst()->m_X;
		m_ScaleCenter.y = -Camera::GetInst()->m_Y;
	}

	D3DXMatrixTransformation2D(&m_wMat, &m_ScaleCenter, 0, &m_Scale, &m_RotationCenter, m_Rotation, &m_Position);

	if (m_Parent)
		m_wMat *= m_Parent->GetMatrix();
	 
	return m_wMat;
}

void Object::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void Object::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void Object::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Object::Rotate(float r)
{
	m_Rotation += r;
}

void Object::SetParent(Object* parent)
{
	m_Parent = parent;
}

void Object::SetTag(const std::string tag)
{
	m_Tag = tag;
}

void Object::Update(float deltaTime, float time)
{
}

void Object::Render()
{
}

void Object::OnCollision(Object* other)
{
}