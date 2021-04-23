#include "Tile.h"
using namespace std;

Tile::Tile()
{
	value = 0;
	flag = false;
	mine = false;
	hidden = true;
	xPos = 0;
	yPos = 0;
	adjacentMines = 0;
}

Tile::Tile(int _value, bool _flag, bool _mine, bool _hidden, int _xPos, int _yPos)
{
	value = _value;
	flag = _flag;
	mine = _mine;
	hidden = _hidden;
	xPos = _xPos;
	yPos = _yPos;
	adjacentMines = 0;
	sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
	sprite.setPosition((float)xPos, (float)yPos);
}

void Tile::AddAdjacentTile(Tile* tile)
{
	adjacentTiles.push_back(tile);
}

void Tile::AddAdjacentTilesTile(Tile* tile)
{
	adjacentTilesTile.push_back(tile);
}

void Tile::changeTexture(string nameTexture)
{
	sprite.setTexture(TextureManager::GetTexture(nameTexture));
}

void Tile::setFlag()
{
	flag = !flag;
}

bool Tile::mineVal()
{
	return mine;
}

bool Tile::flagVal()
{
	return flag;
}

int Tile::xPosVal()
{
	return xPos;
}

int Tile::yPosVal()
{
	return yPos;
}

void Tile::setMineTrue()
{
	mine = true;
}

void Tile::setMine()
{
	mine = true;
	sprite.setTexture(TextureManager::GetTexture("mine"));
}

void Tile::changeToReveal()
{
	sprite.setColor(sf::Color::Transparent);
	hidden = false;
}

void Tile::setEmptySprite()
{
	sprite = sf::Sprite();
	sprite.setPosition((float)xPos, (float)yPos);
}

bool Tile::showHidden()
{
	return hidden;
}

void Tile::setValue(int val)
{
	value = val;
}

void Tile::showFlag()
{
	if (sprite.getTexture())
	{
		flag = false;
		setEmptySprite();
	}
	else
	{
		flag = true;
		sprite.setTexture(TextureManager::GetTexture("flag"));
	}
}

void Tile::clearAdjacentVector()
{
	adjacentTilesTile.clear();
}

int Tile::getAdjacentTiles()
{
	int count = 0;
	for (int i = 0; i < adjacentTiles.size(); i++)
	{
		if (adjacentTiles[i]->mineVal())
			count++;
	}
	return count;
}

void Tile::setNumSprite(string fileName)
{
	sprite.setTexture(TextureManager::GetTexture(fileName));
}

void Tile::makeHidden()
{
	hidden = false;
}

void Tile::AddNonDiagonalTile(Tile* tile)
{
	nonDiagonalNeighbors.push_back(tile);
}

int Tile::getVal()
{
	return value;
}

sf::Sprite Tile::BuildTile()
{
    sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
    sprite.setPosition((float)xPos, (float)yPos);
	return sprite;
	//if flag, put on top
	//if mine, put on bottom
	//if revealed, reveal
}

sf::Sprite Tile::UpdateTile()
{
	return sprite;
}

vector<Tile*>& Tile::getAdjacentTilesVector()
{
	return adjacentTilesTile;
}

vector<Tile*>& Tile::getNonDiagonalVector()
{
	return nonDiagonalNeighbors;
}

Tile::~Tile()
{
	adjacentTiles.clear();
}