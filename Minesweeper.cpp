#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
using namespace std;

int main()
{
    Board board = Board();
    board.GetConfig("boards/config.cfg");
    board.GetMinesVectorRand();
    board.BoardInfo();
    board.BuildBoard();
    board.BuildMinesBoard();
    board.BuildAdjacentTiles();
    board.BuildAdjacentTilesTiles();
    board.BuildNonDiagonalNeighbors();
    board.BuildNumbersBoard();
    board.BuildDigits();
    vector<Tile> baseTiles = board.GetBaseInfo();
    vector<Tile> tiles = board.GetVectorInfo();
    vector<Tile> mineTiles = board.GetMineInfo();
    vector<Tile> flagTiles = board.GetFlagTiles();
    vector<Tile> numbersTiles = board.GetNumbersTiles();
    vector<sf::Sprite> digits = board.GetDigits();
    deque<sf::Sprite> flags = board.BuildFlagDisplay(board.GetFlags(flagTiles));
    vector<sf::Sprite> faces = board.BuildFace(32 * board.GetCols());
    sf::Sprite debugButton = board.BuildDebugMode(32 * board.GetCols());
    vector<sf::Sprite> tests = board.BuildTests(32 * board.GetCols());
    bool debug = false;

    sf::RenderWindow window(sf::VideoMode(32 * board.GetCols(), (32*board.GetRows())+88), "My window");
    window.setTitle("Minesweeper");

    for (int i = 0; i < tiles.size(); i++)
    {
        tiles[i].BuildTile();
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    auto mousePosition = sf::Mouse::getPosition(window);

                    if (!board.getWinStatus() && !board.getLoseStatus())
                    {
                        for (int i = 0; i < tiles.size(); i++)
                        {
                            sf::FloatRect rectangle = tiles[i].UpdateTile().getGlobalBounds();
                            sf::Vector2f mousePosFloat(float(mousePosition.x), float(mousePosition.y));

                            if (rectangle.contains(mousePosFloat) && !flagTiles[i].flagVal())
                            {
                                if (debug && board.getTilesTile(i).mineVal())
                                {
                                    board.getTilesTile(i).changeToReveal();
                                }
                                else if (!board.getTilesTile(i).mineVal())
                                {
                                    board.RemoveEmptyTiles(&board.getTilesTile(i));
                                }
                                else if (!debug)
                                {
                                    board.RemoveEmptyTiles(&board.getTilesTile(i));
                                }
                            }
                        }
                    }

                    sf::FloatRect rectangleFace = faces[0].getGlobalBounds();
                    sf::Vector2f mousePosFloatFace(float(mousePosition.x), float(mousePosition.y));
                    if (rectangleFace.contains(mousePosFloatFace))
                    {
                        board.GetConfig("boards/config.cfg");
                        board.GetMinesVectorRand();
                        board.BuildBoard();
                        board.BuildMinesBoard();
                        board.BuildAdjacentTiles();
                        board.BuildAdjacentTilesTiles();
                        board.BuildNonDiagonalNeighbors();
                        board.BuildNumbersBoard();
                        board.BuildDigits();
                        baseTiles = board.GetBaseInfo();
                        tiles = board.GetVectorInfo();
                        mineTiles = board.GetMineInfo();
                        flagTiles = board.GetFlagTiles();
                        numbersTiles = board.GetNumbersTiles();
                        flags = board.BuildFlagDisplay(board.GetFlags(flagTiles));
                    }

                    sf::FloatRect rectangleDebug = debugButton.getGlobalBounds();
                    if (rectangleDebug.contains(mousePosFloatFace) && !board.getWinStatus() && !board.getLoseStatus())
                    {
                        cout << "Hit Debug Button" << endl;
                        debug = !debug;
                    }

                    for (int i = 0; i < tests.size(); i++)
                    {
                        sf::FloatRect rectangle = tests[i].getGlobalBounds();
                        sf::Vector2f mousePosFloat(float(mousePosition.x), float(mousePosition.y));

                        if (rectangle.contains(mousePosFloat))
                        {
                            cout << "Changed to test " << i + 1 << endl;
                            string fileName = "boards/testboard" + to_string(i + 1) + ".brd";
                            board.GetConfigTests();
                            board.GetMinesVector(fileName);
                            board.BuildBoard();
                            board.BuildMinesBoard();
                            board.BuildAdjacentTiles();
                            board.BuildAdjacentTilesTiles();
                            board.BuildNonDiagonalNeighbors();
                            board.BuildNumbersBoard();
                            board.BuildDigits();
                            baseTiles = board.GetBaseInfo();
                            tiles = board.GetVectorInfo();
                            mineTiles = board.GetMineInfo();
                            flagTiles = board.GetFlagTiles();
                            numbersTiles = board.GetNumbersTiles();
                            flags = board.BuildFlagDisplay(board.GetFlags(flagTiles));
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    auto mousePosition = sf::Mouse::getPosition(window);

                    for (int i = 0; i < flagTiles.size(); i++)
                    {
                        sf::FloatRect rectangle = tiles[i].UpdateTile().getGlobalBounds();
                        sf::Vector2f mousePosFloat(float(mousePosition.x), float(mousePosition.y));

                        if (rectangle.contains(mousePosFloat) && tiles[i].showHidden())
                        {
                            flagTiles[i].showFlag();
                            baseTiles[i].setFlag();
                            board.getTilesTile(i).setFlag();
                            flags = board.BuildFlagDisplay(board.GetFlags(flagTiles));
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        for (int i = 0; i < tiles.size(); i++)
        {
            window.draw(baseTiles[i].UpdateTile());
            window.draw(mineTiles[i].UpdateTile());
            window.draw(numbersTiles[i].UpdateTile());
            for (int i = 0; i < flags.size(); i++)
            {
                window.draw(flags[i]);
            }
            window.draw(board.getTilesTile(i).UpdateTile());
            window.draw(flagTiles[i].UpdateTile());
            window.draw(faces[0]);
            if (board.getWinStatus())
            {
                window.draw(faces[2]);
                if (board.getTilesTile(i).showHidden() && !flagTiles[i].flagVal())
                {
                    flagTiles[i].showFlag();
                    baseTiles[i].setFlag();
                    board.getTilesTile(i).setFlag();
                    flags = board.BuildFlagDisplay(board.GetFlags(flagTiles));
                }
            }
            else if (board.getLoseStatus())
            {
                if (board.getTilesTile(i).showHidden() && mineTiles[i].mineVal())
                {
                    board.getTilesTile(i).changeToReveal();
                }
                window.draw(faces[1]);
            }
            else
                window.draw(faces[0]);
            window.draw(debugButton);
            if (debug == true || board.getLoseStatus())
            {
                for (int j = 0; j < tiles.size(); j++)
                {
                    if (tiles[i].mineVal())
                        window.draw(mineTiles[i].UpdateTile());
                }
            }
            for (int i = 0; i < tests.size(); i++)
            {
                window.draw(tests[i]);
            }
        }
        window.display();

    }

    TextureManager::Clear();
    return 0;
}