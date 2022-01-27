#pragma once
#include "GlobalInclude.h"

struct Runner
{
    int length;
    int column;
    int headRow;
    bool firstLetterWhite;
    char randomGlyph;

    Runner(int col);
    ~Runner();
    void GenerateGlyphs(sf::Text *grid, const int &N_ROW);
};
