#include "Clipper.h"

Clipper::Clipper(int col, int id, const int &N_ROW)
 : column(col), randomGlyph(' '), popLetterWhite(false), idInColumn(id)
{
    lifeSpan = rand() % 90 + 1;
    blinkSpeed = rand() % 10 + 10;
    length = rand() % 5 + 1;
    topRow = rand() % N_ROW;
    popLetterWhite = rand() % 10 + 1 <= 1 ? true : false;
}

Clipper::~Clipper(){}

void Clipper::GenerateGlyphs(sf::Text *grid, const int &N_ROW)
{
    if (lifeSpan % blinkSpeed == 0)
    {
        for (int i = 0; i < length; i++)
        {
            if (topRow + i < N_ROW)
            {
                storedGlyphs[i] = grid[N_ROW * column + topRow + i].getString();
                randomGlyph = rand() % (126 - 33) + 33;
                grid[N_ROW * column + topRow + i].setString(randomGlyph);

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::White);
            }
        }
    } else if (lifeSpan % blinkSpeed == 1 || lifeSpan == 1)
    {
        for (int i = 0; i < length; i++)
        {
            grid[N_ROW * column + topRow + i].setString(storedGlyphs[i]);
            storedGlyphs[i] = "";

            if (popLetterWhite)
                grid[N_ROW * column + topRow + i].setFillColor(sf::Color::Green);
        }
    }

    lifeSpan--;
}