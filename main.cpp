#include "Runner.h"

using namespace std::chrono_literals;

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 800;
const int SCALE_ROW = 16;
const int SCALE_COL = 12;
const int N_COL = WIN_WIDTH / SCALE_COL;
const int N_ROW = WIN_HEIGHT / SCALE_ROW;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Matrix Terminal");

    sf::Font font;
    if (!font.loadFromFile("MatrixCodeNfi-YPPj.otf"))
        return -42;

    sf::Text emptyText;
    emptyText.setFillColor(sf::Color::Green);
    emptyText.setFont(font);
    emptyText.setCharacterSize(20);
    emptyText.setString("a");

    std::cout << "N_ROW : " << N_ROW << "  |  N_COL : " << N_COL << "\n";

    sf::Text grid[N_COL * N_ROW];
    for (int i = 0; i < N_COL * N_ROW; i++)
    {
        grid[i] = emptyText;
        grid[i].setPosition(    SCALE_COL * (i / N_ROW) + 3, 
                                SCALE_ROW * (i % N_ROW) - 5);

        // Markers to get position references
        // TO DELETE
        if (i < N_ROW)
        {
            grid[i].setString(std::to_string(i));
            grid[i].setCharacterSize(10);
        }

        if (i % N_ROW == 0)
        {
            grid[i].setString(std::to_string(i / N_ROW));
            grid[i].setCharacterSize(10);
        }
    }

    srand(time(nullptr));
    Runner r(40);
    //std::vector<Runner> runners;

    while(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int flag = std::cin.get();
            }

        }
        
        r.GenerateGlyphs(grid, N_ROW);

        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        std::this_thread::sleep_for(50ms);
    }

    return EXIT_SUCCESS;
}