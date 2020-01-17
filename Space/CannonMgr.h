#pragma once
enum class CANNON
{
	SPG, //������
	FCANNON, //������
	TOW, //������
	MTRAP, //�ػ�����
	NONE
};
class CannonMgr : public Object
{
	Sprite* m_CannonPanel;

	Sprite* m_SPG;
	Sprite* m_FCannon;
	Sprite* m_TOW;
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
