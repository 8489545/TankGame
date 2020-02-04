#pragma once
enum class CANNON
{
	SPG, //자주포
	BOMBINGTANK, //폭격탱크
	MRL, //미사일런처
	MTRAP, //해상함정
	NONE
};
class CannonMgr : public Object
{
	Sprite* m_CannonPanel;

	Sprite* m_SPG;
	Sprite* m_BombingTank;
	Sprite* m_MRL;
	Sprite* m_MTRAP;
	Sprite* m_GameStart;

	Sprite* m_Cannons[3];
	Sprite* m_Delete;
	TextMgr* m_CannonText;

	std::vector<CANNON> PlayerCannon;
public:
	
	CannonMgr();
	~CannonMgr();

	int m_CannonNum;

	std::vector<CANNON> GetCannon() { return PlayerCannon; }
	

	void AddCannon(CANNON cannon);
	void Delete();
	void Update(float deltaTime,float time);
	void Render();
};

