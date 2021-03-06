#include "Sticker.h"

Sticker::Sticker(int col, int id, const int &N_ROW)
 : column(col), popLetterWhite(false), idInColumn(id)
{
    lifeSpan = rand() % 120 + 30;
    counter = lifeSpan;
    length = rand() % 4 + 1;
    topRow = rand() % N_ROW;
    popLetterWhite = rand() % 20 + 1 <= 1 ? true : false;
    
    for (int i = 0; i < length; i++)
        storedGlyphs[i] = "";
}

Sticker::~Sticker(){}

void Sticker::UpdateGlyphs(sf::Text *grid, const int &N_ROW)
{
    for (int i = 0; i < length; i++)
    {
        if (topRow + i < N_ROW)
        {
            if (counter == lifeSpan)
            {
                for (int j = 0; j < length; j++)
                {
                    int randomGlyph;

                    do
                    {
                        randomGlyph = rand() % (126 - 33) + 33;
                        storedGlyphs[j] = randomGlyph;
                    } while ((randomGlyph > 63 && randomGlyph < 91) || randomGlyph == 96 || (randomGlyph > 47 && randomGlyph < 58));
                }
                
                grid[N_ROW * column + topRow + i].setString(storedGlyphs[i]);

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::White);
            }
            else if (counter <= 1)
            {
                grid[N_ROW * column + topRow + i].setString("");

                if (popLetterWhite)
                    grid[N_ROW * column + topRow + i].setFillColor(sf::Color::Green);
            }
            else if (popLetterWhite)
            {
                grid[N_ROW * column + topRow + i].setString(storedGlyphs[i]);
                grid[N_ROW * column + topRow + i].setFillColor(sf::Color::White);
            }
        }
    }

    counter--;
}