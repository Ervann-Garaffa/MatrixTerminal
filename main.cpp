#include "Runner.h"

using namespace std::chrono_literals;

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const int SCALE_ROW = 18;
const int SCALE_COL = 12;
const int N_COL = WIN_WIDTH / SCALE_COL;
const int N_ROW = WIN_HEIGHT / SCALE_ROW;

int main()
{
    sf::RenderWindow window;//(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Matrix Terminal");
    window.create(sf::VideoMode::getDesktopMode(), "Borderless Fullscreen", sf::Style::Fullscreen);

    sf::Font font;
    if (!font.loadFromFile("MatrixCodeNfi-YPPj.otf"))
        return -42;

    sf::Text emptyText;
    emptyText.setFillColor(sf::Color::Green);
    emptyText.setFont(font);
    emptyText.setCharacterSize(20);
    emptyText.setString(" ");

    sf::Text grid[N_COL * N_ROW];
    for (int i = 0; i < N_COL * N_ROW; i++)
    {
        grid[i] = emptyText;
        grid[i].setPosition(    SCALE_COL * (i / N_ROW) + 3, 
                                SCALE_ROW * (i % N_ROW) - 5);
    }

    srand(time(nullptr));
    int organizer[N_COL][3];
    std::vector<Runner> runners;
    sf::Event event;

    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int flag = std::cin.get();
            }
        }

        for (int i = 0; i < sizeof(organizer) / sizeof(organizer[0]); i++)
        {
            for (int j = 0; j < sizeof(organizer[0]) / sizeof(organizer[0][0]); j++)
            {
                if (!organizer[i][j])
                {
                    organizer[i][j] = 1;
                    runners.emplace_back(Runner(i, j));
                }
            }
        }

        for (int i = 0; i < runners.size(); i++)
        {
            runners[i].GenerateGlyphs(grid, N_ROW);
            if (runners[i].headRow - runners[i].length >= N_ROW)
            {
                organizer[runners[i].column][runners[i].idInColumn] = 0;
                runners.erase(runners.begin() + i);
            }
        }

        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        std::this_thread::sleep_for(30ms);
    }

    return EXIT_SUCCESS;
}