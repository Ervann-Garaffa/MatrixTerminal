#include "Runner.h"
#include "Sticker.h"

using namespace std::chrono_literals;

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const int SCALE_ROW = 16;
const int SCALE_COL = 10;
const int N_COL = WIN_WIDTH / SCALE_COL;
const int N_ROW = WIN_HEIGHT / SCALE_ROW;
const int NMOD_PER_COL = 3;

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
        grid[i].setPosition(    SCALE_COL * (i / N_ROW) + 2, 
                                SCALE_ROW * (i % N_ROW) - 5);
    }

    srand(time(nullptr));
    
    int organizer[N_COL][NMOD_PER_COL];
    std::vector<Runner> runners;
    std::vector<Sticker> stickers;
    std::vector<std::vector<Runner>> runnerGroups;

    sf::Event event;

    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                int flag = std::cin.get();
        }

        for (int i = 0; i < N_COL; i++)
        {
            for (int j = 0; j < NMOD_PER_COL; j++)
            {
                if (!organizer[i][j])
                {
                    organizer[i][j] = rand() % 2 + 1;
                    switch (organizer[i][j])
                    {
                    case 1:
                        runners.emplace_back(Runner(i, j));
                        break;

                    case 2:
                        stickers.emplace_back(Sticker(i, j, N_ROW));
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        }

        while (runnerGroups.size() < 15)
        {
            std::vector<Runner> tempRunnerVector;

            int groupSize = rand() % 8 + 3;
            int startPos = rand() % (N_COL - groupSize - 1);

            for (int i = 0; i < groupSize; i++)
            {
                tempRunnerVector.emplace_back(Runner(startPos + i, 0));
                tempRunnerVector[i].speed = tempRunnerVector[0].speed;
                tempRunnerVector[i].length += 20;

                if (i == 0)
                    tempRunnerVector[0].headRow = rand() % 5;
                else
                    tempRunnerVector[i].headRow = std::abs(tempRunnerVector[0].headRow - (rand() % 5));
            }

            runnerGroups.emplace_back(tempRunnerVector);
        }

        std::cout << "Size of runners array : " << runners.size() << "\n";
        for (int i = 0; i < runners.size(); i++)
        {
            runners[i].GenerateGlyphs(grid, N_ROW);

            // Random chance of dying
            int lives = rand() % 500;
            
            if (runners[i].headRow - runners[i].length >= N_ROW || !lives)
            {
                organizer[runners[i].column][runners[i].idInColumn] = 0;
                runners.erase(runners.begin() + i);
            }
        }
        
        std::cout << "Size of stickers array : " << stickers.size() << "\n";
        for (int i = 0; i < stickers.size(); i++)
        {
            stickers[i].UpdateGlyphs(grid, N_ROW);
            if (stickers[i].counter <= 0)
            {
                organizer[stickers[i].column][stickers[i].idInColumn] = 0;
                stickers.erase(stickers.begin() + i);
            }
        }

        std::cout << "Size of runnerGroups array : " << runnerGroups.size() << "\n";
        for (int i = 0; i < runnerGroups.size(); i++)
        {
            for (int j = 0; j < runnerGroups[i].size(); j++)
            {
                runnerGroups[i][j].GenerateGlyphs(grid, N_ROW);
                if (runnerGroups[i][j].headRow - runnerGroups[i][j].length >= N_ROW)
                {
                    runnerGroups.erase(runnerGroups.begin() + i);
                }
            }
        }
        
        std::cout << "Total number of modifiers : " << runners.size() + stickers.size() + runnerGroups.size() << "\n";

        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        std::this_thread::sleep_for(25ms);
    }

    return EXIT_SUCCESS;
}