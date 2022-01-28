#pragma once
#include "GlobalInclude.h"

struct Sticker
{
    int column;
    int idInColumn;
    int length;

    int topRow;
    int lifeSpan;
    int counter;
    
    bool popLetterWhite;
    std::string storedGlyphs[4];

    Sticker(int col, int id, const int &N_ROW);
    ~Sticker();
    void UpdateGlyphs(sf::Text *grid, const int &N_ROW);
};
