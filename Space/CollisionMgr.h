#pragma once
class CollisionMgr : public Singleton<CollisionMgr>
{
public:
	CollisionMgr();
	~CollisionMgr();

	bool MouseWithBoxSize(Object* obj);
	void MouseWithTagCollide(const std::string tag);
	bool LineToLineCollide(Vec2 Pos1,Vec2 Pos2,Vec2 Pos3,Vec2 Pos4);
};

