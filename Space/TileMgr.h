#pragma once
struct Tile
{
	std::wstring FileName;
	int TileNum;
};
class TileMgr : public Singleton<TileMgr>
{
public:
	TileMgr();
	~TileMgr();

	void Update(float delatTime, float time);
	void Render();

	std::vector<Tile*> m_Tiles;

	int m_Key;
	Vec2 m_CurPos;

	void InsertToPalette(std::wstring filename);
	void SetTilePos(Vec2 pos);
	void DrawMap(int mapdata[],int mapsize);
	void DeletePalette();
};

