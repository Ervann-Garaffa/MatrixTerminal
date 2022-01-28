#include "Clipper.h"

Clipper::Clipper(int col, int id, const int &N_ROW)
 : column(col), popLetterWhite(false), idInColumn(id)
{
    lifeSpan = rand() % 120 + 30;
    counter = lifeSpan;
    blinkSpeed = rand() % 50 + 10;
    length = rand() % 8 + 1;
    topRow = rand() % N_ROW;
    popLetterWhite = rand() % 10 + 1 <= 1 ? true : false;
    
    for (int i = 0; i < length; i++)
        storedGlyphs[i] = "";
}

Clipper::~Clipper(){}

void Clipper::UpdateGlyphs(sf::Text *grid, const int &N_ROW)
{
    std::string tempGlyphs[8];
    
    for (int i = 0; i < length; i++)
    {
        if (topRow + i < N_ROW)
        {
            if (counter == lifeSpan)
            {
                for (int j = 0; j < length; j++)
                {
                    int randGlyph;

                    do
                    {
                        randGlyph = rand() % (126 - 33) + 33;
                        storedGlyphs[j] = randGlyph;
                    } while (randGlyph > 63 && randGlyph < 91);
                }
            }
            else if (counter <= 1)
            {
                grid[N_ROW * column + topRow + i].setString("");

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::Green);
            } 
            else if (counter % blinkSpeed == 0)
            {
                tempGlyphs[i] = storedGlyphs[i];
                storedGlyphs[i] = grid[N_ROW * column + topRow + i].getString();
                grid[N_ROW * column + topRow + i].setString(tempGlyphs[i]);

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::White);
            } 
            else if (counter % blinkSpeed == blinkSpeed / 2)
            {
                tempGlyphs[i] = grid[N_ROW * column + topRow + i].getString();
                grid[N_ROW * column + topRow + i].setString(storedGlyphs[i]);
                storedGlyphs[i] = tempGlyphs[i];

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::Green);
            }
        }
    }

    counter--;
}