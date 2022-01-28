#include "Runner.h"

Runner::Runner(int col, int id)
 : headRow(0), column(col), randomGlyph(' '), popLetterWhite(false), idInColumn(id)
{
    speed = rand() % 8 + 1;
    counter = speed;
    length = rand() % 27 + 3;
    popLetterWhite = rand() % 10 + 1 <= 3 ? true : false;
}

Runner::~Runner(){}

void Runner::GenerateGlyphs(sf::Text *grid, const int &N_ROW)
{
    if (counter == speed)
    {
        randomGlyph = rand() % (126 - 33) + 33;

        if (headRow < N_ROW)
        {
            grid[N_ROW * column + headRow].setString(randomGlyph);

            if (popLetterWhite)
            {
                grid[N_ROW * column + headRow].setFillColor(sf::Color::White);

                if (headRow > 0)
                    grid[N_ROW * column + headRow - 1].setFillColor(sf::Color::Green);
            }
        }

        if (headRow == N_ROW)
            grid[N_ROW * column + headRow - 1].setFillColor(sf::Color::Green);

        if (headRow >= length)
            grid[N_ROW * column + headRow - length].setString("");
        
        headRow++;

        // Later kill Runner
        //if (headRow - length >= N_ROW)
        //    headRow = 0;
    }

    counter--;
    if (!counter)
        counter = speed;
}