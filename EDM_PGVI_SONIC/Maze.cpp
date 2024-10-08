#include "Maze.h"

// Constructor
Maze::Maze(int rows, int cols)
    : mRows(rows), mCols(cols), mWall(sf::Vector2f(100.f, 100.f)) // Tamaño de cada celda
{
    mWall.setFillColor(sf::Color::Green); // Color de las paredes

    // Definir el laberinto (ejemplo simple)
    mMaze = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

// Dibuja el laberinto
void Maze::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < mRows; ++y)
    {
        for (int x = 0; x < mCols; ++x)
        {
            if (mMaze[y][x] == 1)
            {
                mWall.setPosition(x * 100.f, y * 100.f); // Ajusta la posición
                window.draw(mWall);
            }
        }
    }
}

// Verifica si hay una pared en la posición dada
bool Maze::isWall(int x, int y) const
{
    return (x < 0 || x >= mCols || y < 0 || y >= mRows || mMaze[y][x] == 1);
}
