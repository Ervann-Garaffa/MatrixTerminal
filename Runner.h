#pragma once
#include "GlobalInclude.h"

struct Runner
{
    int column;
    int idInColumn;
    int length;

    int headRow;
    int speed;
    int counter;
    
    bool popLetterWhite;
    char randomGlyph;

    Runner(int col, int id);
    ~Runner();
    void GenerateGlyphs(sf::Text *grid, const int &N_ROW);
};
