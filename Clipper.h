#pragma once
#include "GlobalInclude.h"

struct Clipper
{
    int column;
    int idInColumn;
    int length;

    int topRow;
    int blinkSpeed;
    int lifeSpan;
    int counter;
    
    bool popLetterWhite;
    std::string storedGlyphs[6];

    Clipper(int col, int id, const int &N_ROW);
    ~Clipper();
    void UpdateGlyphs(sf::Text *grid, const int &N_ROW);
};
