#include "Board.h"
#include <fstream>
#include "Random.h"

using namespace std;

Board::Board()
{
	cols = 0;
	rows = 0;
	numMines = 0;
	numMinesRand = 0;
	numFlags = 0;
	win = false;
	lose = false;
}

Board::Board(int _columns, int _rows, int _numMines)
{
	cols = _columns;
	rows = _rows;
	numMines = _numMines;
	numMinesRand = _numMines;
	numFlags = _numMines;
	win = false;
	lose = false;
}

void Board::GetConfig(string fileName)
{
	string line;
	ifstream myfile(fileName);
	numMinesRand = 0;
	if (myfile.is_open())
	{
		getline(myfile, line);
		cols = stoi(line);
		getline(myfile, line);
		rows = stoi(line);
		getline(myfile, line);
		numMinesRand = stoi(line);
		myfile.close();
	}
}

void Board::GetConfigTests()
{
	cols = 25;
	rows = 16;
}

int Board::GetRows()
{
	return rows;
}

int Board::GetCols()
{
	return cols;
}

int Board::GetMines()
{
	return numMines;
}

int Board::GetMinesRand()
{
	return numMinesRand;
}

int Board::GetFlags(vector<Tile>& list)
{
	int count = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].flagVal())
			count++;
	}
	return numFlags - count;
}

void Board::BoardInfo()
{
	cout << cols << endl;
	cout << rows << endl;
	cout << numMines << endl;
}

void Board::BuildBoard()
{
	numFlags = 0;
	tiles.clear();
	baseTiles.clear();
	flagTiles.clear();
	numFlags = numMines;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Tile tile = Tile(0, false, false, true, j * TextureManager::GetTexture("tile_revealed").getSize().x, i * TextureManager::GetTexture("tile_revealed").getSize().y);
			tile.BuildTile();
			tiles.push_back(tile);
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Tile tile = Tile(0, false, false, false, j * TextureManager::GetTexture("tile_revealed").getSize().x, i * TextureManager::GetTexture("tile_revealed").getSize().y);
			tile.changeTexture("tile_revealed");
			baseTiles.push_back(tile);
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Tile tile = Tile(0, false, false, true, j * TextureManager::GetTexture("tile_revealed").getSize().x, i * TextureManager::GetTexture("tile_revealed").getSize().y);
			tile.setEmptySprite();
			flagTiles.push_back(tile);
		}
	}
	for (int i = 0; i < tiles.size(); i++)
	{
		if (mines[i])
		{
			baseTiles[i].setMineTrue();
			tiles[i].setMineTrue();
		}
	}
}

void Board::BuildMinesBoard()
{
	minesTiles.clear();
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].mineVal())
		{
			Tile tile = Tile(0, false, true, false, tiles[i].xPosVal(), tiles[i].yPosVal());
			tile.setMine();
			minesTiles.push_back(tile);
		}
		else
		{
			Tile tile = Tile(0, false, false, false, tiles[i].xPosVal(), tiles[i].yPosVal());
			minesTiles.push_back(tile);
		}
	}
}

void Board::BuildNumbersBoard()
{
	numbersTiles.clear();
	for (int i = 0; i < baseTiles.size(); i++)
	{
		if (tiles[i].mineVal())
		{
			Tile tile = Tile(0, false, true, false, baseTiles[i].xPosVal(), baseTiles[i].yPosVal());
			tile.setMineTrue();
			tile.setEmptySprite();
			numbersTiles.push_back(tile);
		}
		else
		{
			Tile tile = Tile(0, false, false, false, tiles[i].xPosVal(), tiles[i].yPosVal());
			if (baseTiles[i].getAdjacentTiles() == 0)
			{
				tiles[i].setValue(0);
				baseTiles[i].setValue(0);
				tile.setValue(0);
				tile.setEmptySprite();
			}
			else if (baseTiles[i].getAdjacentTiles() == 1)
			{
				tiles[i].setValue(1);
				baseTiles[i].setValue(1);
				tile.setValue(1);
				tile.setNumSprite("number_1");
			}
			else if (baseTiles[i].getAdjacentTiles() == 2)
			{
				tiles[i].setValue(2);
				baseTiles[i].setValue(2);
				tile.setValue(2);
				tile.setNumSprite("number_2");
			}
			else if (baseTiles[i].getAdjacentTiles() == 3)
			{
				tiles[i].setValue(3);
				baseTiles[i].setValue(3);
				tile.setValue(3);
				tile.setNumSprite("number_3");
			}
			else if (baseTiles[i].getAdjacentTiles() == 4)
			{
				tiles[i].setValue(4);
				baseTiles[i].setValue(4);
				tile.setValue(4);
				tile.setNumSprite("number_4");
			}
			else if (baseTiles[i].getAdjacentTiles() == 5)
			{
				tiles[i].setValue(5);
				baseTiles[i].setValue(5);
				tile.setValue(5);
				tile.setNumSprite("number_5");
			}
			else if (baseTiles[i].getAdjacentTiles() == 6)
			{
				tiles[i].setValue(6);
				baseTiles[i].setValue(6);
				tile.setValue(6);
				tile.setNumSprite("number_6");
			}
			else if (baseTiles[i].getAdjacentTiles() == 7)
			{
				tiles[i].setValue(7);
				baseTiles[i].setValue(7);
				tile.setValue(7);
				tile.setNumSprite("number_7");
			}
			else if (baseTiles[i].getAdjacentTiles() == 8)
			{
				tiles[i].setValue(8);
				baseTiles[i].setValue(8);
				tile.setValue(8);
				tile.setNumSprite("number_8");
			}
			else
			{
				tile.setEmptySprite();
			}
			numbersTiles.push_back(tile);
		}
	}
}

void Board::BuildAdjacentTiles()
{
	for (int i = 0; i < baseTiles.size(); i++)
	{
		if ((i + 1) % cols == 1)
		{
			if (i == 0)
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols + 1]);
			}
			else if ((i + cols) == rows * cols)
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols + 1]);
			}
			else
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols + 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols + 1]);
			}
		}
		else if ((i + 1) % cols == 0)
		{
			if ((i + 1) == cols)
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols - 1]);
			}
			else if ((i + 1) == rows * cols)
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols - 1]);
			}
			else
			{
				baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i + cols - 1]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
				baseTiles[i].AddAdjacentTile(&baseTiles[i - cols - 1]);
			}
		}
		else if (((i + 1) / cols) < 1)
		{
			baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols - 1]);
		}
		else if (((i + 1) + cols) / cols == rows)
		{
			baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols - 1]);
		}
		else
		{
			baseTiles[i].AddAdjacentTile(&baseTiles[i + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i + cols - 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols + 1]);
			baseTiles[i].AddAdjacentTile(&baseTiles[i - cols - 1]);
		}
	}
}

void Board::BuildNonDiagonalNeighbors()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if ((i + 1) % cols == 1)
		{
			if (i == 0)
			{
				tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
			}
			else if ((i + cols) == rows * cols)
			{
				tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
			}
			else
			{
				tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
				tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
			}
		}
		else if ((i + 1) % cols == 0)
		{
			if ((i + 1) == cols)
			{
				tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
			}
			else if ((i + 1) == rows * cols)
			{
				tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
			}
			else
			{
				tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
				tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
				tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
			}
		}
		else if (((i + 1) / cols) < 1)
		{
			tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
		}
		else if (((i + 1) + cols) / cols == rows)
		{
			tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
		}
		else
		{
			tiles[i].AddNonDiagonalTile(&tiles[i + 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i - 1]);
			tiles[i].AddNonDiagonalTile(&tiles[i + cols]);
			tiles[i].AddNonDiagonalTile(&tiles[i - cols]);
		}
	}
}

void Board::BuildAdjacentTilesTiles()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if ((i + 1) % cols == 1)
		{
			if (i == 0)
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols + 1]);
			}
			else if ((i + cols) == rows * cols)
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols + 1]);
			}
			else
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols + 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols + 1]);
			}
		}
		else if ((i + 1) % cols == 0)
		{
			if ((i + 1) == cols)
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols - 1]);
			}
			else if ((i + 1) == rows * cols)
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols - 1]);
			}
			else
			{
				tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i + cols - 1]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
				tiles[i].AddAdjacentTilesTile(&tiles[i - cols - 1]);
			}
		}
		else if (((i + 1) / cols) < 1)
		{
			tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols - 1]);
		}
		else if (((i + 1) + cols) / cols == rows)
		{
			tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols - 1]);
		}
		else
		{
			tiles[i].AddAdjacentTilesTile(&tiles[i + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i + cols - 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols + 1]);
			tiles[i].AddAdjacentTilesTile(&tiles[i - cols - 1]);
		}
	}
}

Tile& Board::getTilesTile(int index)
{
	return tiles[index];
}

void Board::RemoveEmptyTiles(Tile* tile)
{
	if (tile->flagVal())
		return;
	else
		tile->changeToReveal();
	vector<Tile*> vectorDiag;
	vectorDiag = tile->getAdjacentTilesVector();
	if (tile->mineVal())
		return;
	if (tile->getVal() != 0)
		return;
	for (int i = 0; i < vectorDiag.size(); i++)
	{
		if (!vectorDiag[i]->mineVal() && vectorDiag[i]->showHidden())
			RemoveEmptyTiles(vectorDiag[i]);
	}
}

void Board::resetStatus()
{
	win = false;
	lose = false;
}

bool Board::getWinStatus()
{
	win = false;
	int count = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	for (int i = 0; i < tiles.size(); i++)
	{
		if (!tiles[i].showHidden() && !tiles[i].mineVal())
			count++;
	}
	if (count == tiles.size() - numMines)
		win = true;
	return win;
}

bool Board::getLoseStatus()
{
	lose = false;
	int count = 0; 
	for (int i = 0; i < tiles.size(); i++)
	{
		if (!tiles[i].showHidden() && tiles[i].mineVal())
			count++;
	}
	if (count > 0)
		lose = true;
	return lose;
}

void Board::BuildDigits()
{
	digits.clear();
	// , sf::IntRect(0, 0, 21, 32)
	for (int i = 0; i < 11; i++)
	{
		sf::Sprite zeroS;
		zeroS.setTexture(TextureManager::GetTexture("digits"));
		zeroS.setTextureRect(sf::IntRect(21*i, 0, 21, 32));
		zeroS.setPosition(21 + 21*i, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
		digits.push_back(zeroS);
	}
}

deque<sf::Sprite>& Board::BuildFlagDisplay(int num)
{
	display.clear();
	if (num < 0)
	{
		int newTempNum = (-1) * num;
		if (newTempNum >= 100)
		{
			int tempNum = newTempNum;
			int position = 42;
			while (tempNum > 0)
			{
				sf::Sprite number = digits[tempNum % 10];
				tempNum /= 10;
				display.push_front(number);
			}
			for (int i = 0; i < display.size(); i++)
			{
				display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				position += 21;
			}
			sf::Sprite neg = digits[10];
			neg.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
			display.push_front(neg);
		}
		else if (newTempNum < 100)
		{
			if (newTempNum < 10)
			{
				int tempNum = newTempNum;
				int position = 84;
				while (tempNum > 0)
				{
					sf::Sprite number = digits[tempNum % 10];
					tempNum /= 10;
					display.push_front(number);
				}
				for (int i = 0; i < display.size(); i++)
				{
					display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
					position += 21;
				}
				sf::Sprite zero = digits[0];
				zero.setPosition(63, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				display.push_front(zero);
				sf::Sprite zero2 = digits[0];
				zero2.setPosition(42, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				display.push_front(zero2);
				sf::Sprite neg = digits[10];
				neg.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				display.push_front(neg);
			}
			else
			{
				int tempNum = newTempNum;
				int position = 63;
				while (tempNum > 0)
				{
					sf::Sprite number = digits[tempNum % 10];
					tempNum /= 10;
					display.push_front(number);
				}
				for (int i = 0; i < display.size(); i++)
				{
					display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
					position += 21;
				}
				sf::Sprite zero = digits[0];
				zero.setPosition(42, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				display.push_front(zero);
				sf::Sprite neg = digits[10];
				neg.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				display.push_front(neg);
			}
		}
	}
	else if (num == 0)
	{
		sf::Sprite zero = digits[0];
		zero.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
		display.push_front(zero);
		sf::Sprite zero2 = digits[0];
		zero2.setPosition(42, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
		display.push_front(zero2);
		sf::Sprite zero3 = digits[0];
		zero3.setPosition(63, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
		display.push_front(zero3);
	}
	else if (num < 100)
	{
		if (num < 10)
		{
			int tempNum = num;
			int position = 63;
			while (tempNum > 0)
			{
				sf::Sprite number = digits[tempNum % 10];
				tempNum /= 10;
				display.push_front(number);
			}
			for (int i = 0; i < display.size(); i++)
			{
				display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				position += 21;
			}
			sf::Sprite zero = digits[0];
			zero.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
			display.push_front(zero);
			sf::Sprite zero2 = digits[0];
			zero2.setPosition(42, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
			display.push_front(zero2);
		}
		else
		{
			int tempNum = num;
			int position = 42;
			while (tempNum > 0)
			{
				sf::Sprite number = digits[tempNum % 10];
				tempNum /= 10;
				display.push_front(number);
			}
			for (int i = 0; i < display.size(); i++)
			{
				display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
				position += 21;
			}
			sf::Sprite zero = digits[0];
			zero.setPosition(21, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
			display.push_front(zero);
		}
	}
	else if (num >= 100)
	{
		int tempNum = num;
		int position = 21;
		while (tempNum > 0)
		{
			sf::Sprite number = digits[tempNum % 10];
			tempNum /= 10;
			display.push_front(number);
		}
		for (int i = 0; i < display.size(); i++)
		{
			display[i].setPosition(position, rows * TextureManager::GetTexture("tile_revealed").getSize().y);
			position += 21;
		}
	}
	return display;
}

vector<sf::Sprite>& Board::BuildFace(int width)
{
	faces.clear();
	sf::Sprite happyFace;
	happyFace.setTexture(TextureManager::GetTexture("face_happy"));
	happyFace.setPosition((width / 2) - (TextureManager::GetTexture("face_happy").getSize().x/2), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	faces.push_back(happyFace);

	sf::Sprite sadFace;
	sadFace.setTexture(TextureManager::GetTexture("face_lose"));
	sadFace.setPosition((width / 2) - (TextureManager::GetTexture("face_happy").getSize().x / 2), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	faces.push_back(sadFace);

	sf::Sprite winFace;
	winFace.setTexture(TextureManager::GetTexture("face_win"));
	winFace.setPosition((width / 2) - (TextureManager::GetTexture("face_happy").getSize().x / 2), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	faces.push_back(winFace);

	return faces;
}

sf::Sprite Board::BuildDebugMode(int width)
{
	sf::Sprite debugMode;
	debugMode.setTexture(TextureManager::GetTexture("debug"));
	debugMode.setPosition((width / 2) + (1.5 * TextureManager::GetTexture("debug").getSize().x), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	return debugMode;
}

vector<sf::Sprite>& Board::BuildTests(int width)
{
	tests.clear();
	sf::Sprite testOne;
	testOne.setTexture(TextureManager::GetTexture("test_1"));
	testOne.setPosition((width / 2) + (1.5 * TextureManager::GetTexture("debug").getSize().x) + (TextureManager::GetTexture("debug").getSize().x), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	tests.push_back(testOne);

	sf::Sprite testTwo;
	testTwo.setTexture(TextureManager::GetTexture("test_2"));
	testTwo.setPosition((width / 2) + (1.5 * TextureManager::GetTexture("debug").getSize().x) + (TextureManager::GetTexture("debug").getSize().x) + (TextureManager::GetTexture("test_1").getSize().x), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	tests.push_back(testTwo);

	sf::Sprite testThree;
	testThree.setTexture(TextureManager::GetTexture("test_3"));
	testThree.setPosition((width / 2) + (1.5 * TextureManager::GetTexture("debug").getSize().x) + (TextureManager::GetTexture("debug").getSize().x) + (TextureManager::GetTexture("test_1").getSize().x) + (TextureManager::GetTexture("test_2").getSize().x), rows * TextureManager::GetTexture("tile_revealed").getSize().y);
	tests.push_back(testThree);

	return tests;
}

void Board::GetMinesVector(string fileName)
{
	mines.clear();
	numMines = 0;
	ifstream myfile(fileName);
	char ch;
	while (myfile >> ch)
	{
		if (ch - '0' == 1)
		{
			mines.push_back(true);
			numMines++;
		}
		else
			mines.push_back(false);
	}
}

void Board::GetMinesVectorRand()
{
	mines.clear();
	int tempMines = numMinesRand;
	numMines = numMinesRand;
	for (int i = 0; i < (rows * cols); i++)
	{
		mines.push_back(false);
	}
	while (tempMines > 0)
	{
		int mine = Random::Int(0, mines.size()-1);
		if (mines[mine] == false)
		{
			mines[mine] = true;
			tempMines--;
		}
	}
}

vector<Tile>& Board::GetVectorInfo()
{
	return tiles;
}

vector<Tile>& Board::GetMineInfo()
{
	return minesTiles;
}

vector<Tile>& Board::GetBaseInfo()
{
	return baseTiles;
}

vector<Tile>& Board::GetFlagTiles()
{
	return flagTiles;
}

vector<Tile>& Board::GetNumbersTiles()
{
	return numbersTiles;
}

vector<sf::Sprite>& Board::GetDigits()
{
	return digits;
}