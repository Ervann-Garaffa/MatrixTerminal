#pragma once
#include "GlobalInclude.h"

struct Drop
{
    sf::Vector2i origin;
    int maxRadius;
    int radCounter;
    int speed;
    int speedCounter;

    Drop();
    ~Drop();
    void Reset();
    void Start(const int &N_COL, const int &N_ROW);
    void UpdateColors(sf::Text *grid, const int &N_COL, const int &N_ROW);
};
