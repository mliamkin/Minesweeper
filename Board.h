#pragma once
#include <vector>
#include <deque>
#include "Tile.h"
#include "TextureManager.h"
using namespace std;

class Board
{
	int cols;
	int rows;
	int numMines;
	int numMinesRand;
	int numFlags;
	bool win;
	bool lose;
	vector<Tile> baseTiles;
	vector<Tile> tiles;
	vector<Tile> minesTiles;
	vector<Tile> flagTiles;
	vector<Tile> numbersTiles;
	vector<sf::Sprite> digits;
	deque<sf::Sprite> display;
	vector<sf::Sprite> faces;
	vector<sf::Sprite> tests;
	vector<bool> mines;
public:
	Board();
	Board(int _columns, int _rows, int _numMines);
	void GetConfig(string fileName);
	void GetConfigTests();
	int GetRows();
	int GetCols();
	int GetMines();
	int GetMinesRand();
	int GetFlags(vector<Tile>& list);
	void BoardInfo();
	void BuildBoard();
	void GetMinesVector(string fileName);
	void GetMinesVectorRand();
	void BuildMinesBoard();
	void BuildNumbersBoard();
	void BuildAdjacentTiles();
	void BuildAdjacentTilesTiles();
	void BuildNonDiagonalNeighbors();
	void BuildDigits();
	void RemoveEmptyTiles(Tile* tile);
	void resetStatus();
	bool getWinStatus();
	bool getLoseStatus();
	Tile& getTilesTile(int index);
	sf::Sprite BuildDebugMode(int width);
	vector<sf::Sprite>& BuildTests(int width);
	vector<sf::Sprite>& BuildFace(int width);
	deque<sf::Sprite>& BuildFlagDisplay(int num);
	vector<Tile>& GetBaseInfo();
	vector<Tile>& GetVectorInfo();
	vector<Tile>& GetMineInfo();
	vector<Tile>& GetFlagTiles();
	vector<Tile>& GetNumbersTiles();
	vector<sf::Sprite>& GetDigits();
};

