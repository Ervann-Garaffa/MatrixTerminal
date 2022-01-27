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
    
    bool popLetterWhite;
    char randomGlyph;
    std::string storedGlyphs[5];

    Clipper(int col, int id, const int &N_ROW);
    ~Clipper();
    void GenerateGlyphs(sf::Text *grid, const int &N_ROW);
};
