#include "Drop.h"

Drop::Drop()
{
    this->Reset();
}

Drop::~Drop() {}

void Drop::Reset()
{
    origin.x = 0;
    origin.y = 0;
    maxRadius = 0;
    radCounter = 1;
    speed = 0;
    speedCounter = 0;
}

void Drop::Start(const int &N_COL, const int &N_ROW)
{
    origin.x = rand() % N_COL;
    origin.y = rand() % N_ROW;

    maxRadius = rand() % (N_ROW / 2 - 5) + 5;
    radCounter = 1;
    speed = rand() % 8 + 1;
    speedCounter = speed;
}

void Drop::UpdateColors(sf::Text *grid, const int &N_COL, const int &N_ROW)
{
    /*
    for (int i = origin.x - radCounter; i <= origin.x + radCounter; i++)
    {
        for (int j = origin.y - radCounter; i <= origin.y + radCounter; j++)
        {
            if (i >= 0 && i <= N_COL && j >= 0 && j <= N_ROW)
            {
                grid[N_ROW * i + j].setFillColor(sf::Color::White);
            }
        }
    }
    */

    /*
    std::cout << "Speed counter : " << speedCounter << " | Rad Counter : " << radCounter << " | Max Rad = " << maxRadius << "\n";
    std::cout << "Ox : " << origin.x << " | Oy : " << origin.y << "\n";
    */
    speedCounter --;

    if (!speedCounter)
    {
        speedCounter = speed;
        radCounter ++;
    }

    if (radCounter >= maxRadius)
        this->Reset();
}