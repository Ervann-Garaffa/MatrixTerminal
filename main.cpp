#include "Runner.h"
#include "Sticker.h"
#include "Drop.h"

using namespace std::chrono_literals;

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const int SCALE_ROW = 16;
const int SCALE_COL = 10;
const int N_COL = WIN_WIDTH / SCALE_COL;
const int N_ROW = WIN_HEIGHT / SCALE_ROW;
const int NMOD_PER_COL = 6;
const int MAX_MOD_HIGH = N_COL * NMOD_PER_COL;
const int MAX_MOD_LOW = MAX_MOD_HIGH / 20;

int main()
{
    // Config of window + font
    sf::RenderWindow window;//(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Matrix Terminal");
    window.create(sf::VideoMode::getDesktopMode(), "Borderless Fullscreen", sf::Style::Fullscreen);

    sf::Font font;
    if (!font.loadFromFile("MatrixCodeNfi-YPPj.otf"))
        return -42;

    // Create empty grid of characters
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

    // Random generator init
    srand(time(nullptr));
    
    // Modifier objects declarations
    int organizer[N_COL][NMOD_PER_COL];
    std::vector<Runner> runners;
    std::vector<Sticker> stickers;
    Drop drop;
    std::vector<std::vector<Runner>> runnerGroups;

    int targetMaxMod = 20;
    float incTarget = 5.f;
    float inc = 0.1f;

    // Window loop
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

        incTarget += inc;
        if ((inc > 0 && incTarget > targetMaxMod) || (inc < 0 && incTarget < targetMaxMod))
        {
            do
            {
                targetMaxMod = rand() % (MAX_MOD_HIGH - MAX_MOD_LOW) + MAX_MOD_LOW;
            } while (targetMaxMod == runners.size() + stickers.size());
            
            inc = (float)((rand() % 5 + 2)*(rand() % 5 + 2)*(rand() % 5 + 2)) / 50;
            incTarget = runners.size() + stickers.size();

            if (runners.size() + stickers.size() > targetMaxMod)
                inc = - inc;
        }

        std::cout << "Inc : " << inc << " | incTarget : " << incTarget << " | targetMaxMod : " << targetMaxMod << 
            " | Unique Mods number : " << runners.size() + stickers.size() << " | Runner group number : " << + runnerGroups.size() << "\n";

        // Unique modifiers creation
        while (runners.size() + stickers.size() < incTarget)
        {
            int i = rand() % N_COL;
            int j = rand() % NMOD_PER_COL;

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

            // Runner groups creation
            if (runnerGroups.size() < (runners.size() + stickers.size() + runnerGroups.size()) / 20)
            {
                std::vector<Runner> tempRunnerVector;

                int groupSize = rand() % 6 + 2;
                int startPos = rand() % (N_COL - groupSize - 1);

                for (int i = 0; i < groupSize; i++)
                {
                    tempRunnerVector.emplace_back(Runner(startPos + i, 0));
                    tempRunnerVector[i].speed = tempRunnerVector[0].speed;
                    tempRunnerVector[i].length += rand() % 25 + 5;

                    if (i == 0)
                        tempRunnerVector[0].headRow = rand() % 5;
                    else
                        tempRunnerVector[i].headRow = std::abs(tempRunnerVector[0].headRow - (rand() % 5));
                }

                runnerGroups.emplace_back(tempRunnerVector);
            }
        }

        if (!drop.speed && !(rand() % 100))
            drop.Start(N_COL, N_ROW);

        // Apply modifiers' behaviors
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
        
        for (int i = 0; i < stickers.size(); i++)
        {
            stickers[i].UpdateGlyphs(grid, N_ROW);
            if (stickers[i].counter <= 0)
            {
                organizer[stickers[i].column][stickers[i].idInColumn] = 0;
                stickers.erase(stickers.begin() + i);
            }
        }

        for (int i = 0; i < runnerGroups.size(); i++)
        {
            for (int j = 0; j < runnerGroups[i].size(); j++)
            {
                runnerGroups[i][j].GenerateGlyphs(grid, N_ROW);
                if (runnerGroups[i][j].headRow - runnerGroups[i][j].length >= N_ROW + 10)
                    runnerGroups.erase(runnerGroups.begin() + i);
            }
        }
        
        // Render grid
        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        // Set frame time
        std::this_thread::sleep_for(45ms);
    }

    return EXIT_SUCCESS;
}