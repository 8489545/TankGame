#pragma once
class EffectMgr : public Object
{
	Animation* Effect;
public:
	EffectMgr(std::wstring filename,int start,int end,Vec2 Pos);
	~EffectMgr();


	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);
};

