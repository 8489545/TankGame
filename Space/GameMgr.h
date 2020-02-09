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

enum class TURN
{
	PLAYER,
	ENEMY,
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

	TURN m_Turn;

	void NextStage(STAGE stage);
	void ChangeNextStage();
	void CreatePlayer();
	void ChangeTurn();
};

