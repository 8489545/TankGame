#include "stdafx.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::MouseWithBoxSize(Object* obj)
{
	Vec2 Mouse = INPUT->GetMousePos();
	if (Mouse.x > obj->m_Position.x - obj->m_Size.x
		&& Mouse.x < obj->m_Position.x + obj->m_Size.x / 2
		&& Mouse.y > obj->m_Position.y - obj->m_Size.y
		&& Mouse.y < obj->m_Position.y + obj->m_Size.y / 2)
	{
		return true;
	}

	return false;
}

void CollisionMgr::MouseWithTagCollide(const std::string tag)
{
	Vec2 Mouse = INPUT->GetMousePos();
	for (auto& iter : ObjMgr->m_Objects)
	{ 
		if (iter->m_Tag == tag)
		{
			if (iter->m_Collision.left <= Mouse.x && Mouse.x <= iter->m_Collision.right)
			{
				if (iter->m_Collision.top <= Mouse.y && Mouse.y <= iter->m_Collision.bottom)
				{
					iter->m_MouseCol = true;
				}
			}
			else
			{
				iter->m_MouseCol = false;
			}
		}
	}
}

bool CollisionMgr::LineToLineCollide(Vec2 Pos1, Vec2 Pos2, Vec2 Pos3, Vec2 Pos4)
{
	float den;
	float CondA;
	float CondB;

	den = (Pos4.y, -Pos3.y) * (Pos2.x - Pos1.x) - (Pos4.x - Pos3.x) * (Pos2.y - Pos1.y);

	if (den == 0)
		return false;


	CondA = ((Pos4.x - Pos3.x) * (Pos1.y - Pos3.y) - (Pos4.y - Pos3.y) * (Pos1.x - Pos3.x)) / den;

	CondB = ((Pos2.x - Pos1.x) * (Pos1.y - Pos3.y) - (Pos2.y - Pos1.y) * (Pos1.x - Pos3.x)) / den;

	if (CondA < 0.f || CondA > 1.f || CondB < 0.f || CondB > 1.f)
		return false;


	return true;
}
