#pragma once
enum class STAGE
{
	BEAK,
	DAE,
	SO,
	U,
	YEON,
	NONE
};
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	std::vector<CANNON> m_CannonVec;
	STAGE m_Next;

	bool m_isPlayer;

	void NextStage(STAGE stage);
	void ChangeNextStage();
	void CreatePlayer();
};

