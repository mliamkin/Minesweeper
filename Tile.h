#pragma once
#include "TextureManager.h"
using namespace std;

class Tile
{
	int value;
	bool flag;
	bool mine;
    bool hidden;
	int adjacentMines;
    int xPos;
    int yPos;
    sf::Sprite sprite;
    vector<Tile*> adjacentTiles;
    vector<Tile*> adjacentTilesTile;
    vector<Tile*> nonDiagonalNeighbors;
public:
    Tile();
    Tile(int _value, bool _flag, bool _mine, bool _hidden, int _xPos, int _yPos);
    void setMine();
    void setFlag();
    void setMineTrue();
    void changeToReveal();
    void makeHidden();
    bool mineVal();
    bool flagVal();
    bool showHidden();
    int xPosVal();
    int yPosVal();
    int getVal();
    void clearAdjacentVector();
    void changeTexture(string nameTexture);
    void showFlag();
    void AddAdjacentTile(Tile* tile);
    void AddAdjacentTilesTile(Tile* tile);
    void AddNonDiagonalTile(Tile* tile);
    void setEmptySprite();
    void setNumSprite(string fileName);
    void setValue(int val);
    int getAdjacentTiles();
    vector<Tile*>& getAdjacentTilesVector();
    vector<Tile*>& getNonDiagonalVector();
    sf::Sprite BuildTile();
    sf::Sprite UpdateTile();
    ~Tile();
};

