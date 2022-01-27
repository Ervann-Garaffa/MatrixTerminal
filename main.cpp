#include "Runner.h"
#include "Clipper.h"
#include "Killer.h"

using namespace std::chrono_literals;

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;
const int SCALE_ROW = 18;
const int SCALE_COL = 12;
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
    std::vector<Clipper> clippers;
    std::vector<Killer> killers;
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
                    organizer[i][j] = rand() % 2 + 1; // Only Runners and Clippers generated
                    switch (organizer[i][j])
                    {
                    case 1:
                        runners.emplace_back(Runner(i, j));
                        break;

                    case 2:
                        clippers.emplace_back(Clipper(i, j, N_ROW));
                        break;
                    
                    /* case 3:
                        killers.emplace_back(Killer(i, j));
                        break; */
                    
                    default:
                        break;
                    }
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

        for (int i = 0; i < clippers.size(); i++)
        {
            clippers[i].GenerateGlyphs(grid, N_ROW);
            if (!clippers[i].lifeSpan)
            {
                organizer[clippers[i].column][clippers[i].idInColumn] = 0;
                clippers.erase(clippers.begin() + i);
            }
        }
        
        // Implement killer actions failed
        // Too many kills? Disrespect of vector sizes?
        // => Floating point exception

        /* for (int i = 0; i < killers.size(); i++)
        {
            int typeOfKill = rand() % 3 + 1;
            int posKill = 0;
            int col = 0;
            int id = 0;

            std::cout << typeOfKill << "\n";

            switch (typeOfKill)
            {
            case 1:
                posKill = rand() % runners.size();
                col = runners[posKill].column;
                id = runners[posKill].idInColumn;
                runners.erase(runners.begin() + posKill);
                organizer[col][id] = 0;
                break;

            case 2:
                posKill = rand() % clippers.size();
                col = clippers[posKill].column;
                id = clippers[posKill].idInColumn;
                clippers.erase(clippers.begin() + posKill);
                organizer[col][id] = 0;
                break;
            
            case 3:
                posKill = rand() % killers.size();
                col = killers[posKill].column;
                id = killers[posKill].idInColumn;
                killers.erase(killers.begin() + posKill);
                organizer[col][id] = 0;
                break;
            
            default:
                break;
            }
                        
        } */

        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        std::this_thread::sleep_for(30ms);
    }

    return EXIT_SUCCESS;
}