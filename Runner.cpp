#include "Runner.h"

Runner::Runner(int col)
    : headRow(0), column(col), randomGlyph(' '), firstLetterWhite(true)
{
    length = rand() % 10 + 10;
}

Runner::~Runner()
{

}

void Runner::GenerateGlyphs(sf::Text *grid, const int &N_ROW)
{
    randomGlyph = rand() % (126 - 33) + 33;

    if (headRow < N_ROW)
    {
        grid[N_ROW * column + headRow].setString(randomGlyph);

        if (firstLetterWhite)
        {
            grid[N_ROW * column + headRow].setFillColor(sf::Color::White);

            if (headRow > 0)
                grid[N_ROW * column + headRow - 1].setFillColor(sf::Color::Green);
        }
    }

    if (headRow >= length)
    {
        grid[N_ROW * column + headRow - length].setString("");
    }
    
    headRow++;

    // Later kill Runner
    if (headRow - length >= N_ROW)
        headRow = 0;
}