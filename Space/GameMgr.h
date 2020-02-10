#pragma once
enum class STAGE
{
	BEAK,
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
	bool m_isEnemy;

	bool m_BeakClear;

	TURN m_Turn;

	void NextStage(STAGE stage);
	void ChangeNextStage();
	void CreatePlayer();
	void CreateEnemy();
	void ChangeTurn();
	void SetTurn(TURN turn);
	TURN GetTurn();
};

