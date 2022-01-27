#pragma once
#include "GlobalInclude.h"

struct Killer
{
    int column;
    int idInColumn;

    Killer(int col, int id);
    ~Killer();
};
