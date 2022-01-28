#include "Runner.h"
#include "Clipper.h"
#include "Sticker.h"
#include "Killer.h"

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
    std::vector<Clipper> clippers;
    std::vector<Sticker> stickers;
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
                    organizer[i][j] = rand() % 3 + 1; // Only Runners, Clippers and Stickers generated
                    switch (organizer[i][j])
                    {
                    case 1:
                        runners.emplace_back(Runner(i, j));
                        break;

                    case 2:
                        clippers.emplace_back(Clipper(i, j, N_ROW));
                        break;
                    
                    case 3:
                        stickers.emplace_back(Sticker(i, j, N_ROW));
                        break;
                    
                    case 4:
                        killers.emplace_back(Killer(i, j));
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        }

        std::cout << "Size of runners array : " << runners.size() << "\n";
        for (int i = 0; i < runners.size(); i++)
        {
            runners[i].GenerateGlyphs(grid, N_ROW);
            if (runners[i].headRow - runners[i].length >= N_ROW)
            {
                organizer[runners[i].column][runners[i].idInColumn] = 0;
                runners.erase(runners.begin() + i);
            }
        }

        std::cout << "Size of clippers array : " << clippers.size() << "\n";
        for (int i = 0; i < clippers.size(); i++)
        {
            clippers[i].UpdateGlyphs(grid, N_ROW);
            if (clippers[i].counter <= 0)
            {
                organizer[clippers[i].column][clippers[i].idInColumn] = 0;
                clippers.erase(clippers.begin() + i);
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
        
        // Implement killer actions failed
        // Too many kills? Disrespect of vector sizes?
        // => Floating point exception

        // std::cout << "Size of killers array : " << killers.size() << "\n";
        for (int i = 0; i < killers.size(); i++)
        {
            int typeOfKill = rand() % 4 + 1;
            int posKill = 0;
            int col = 0;
            int id = 0;

            switch (typeOfKill)
            {
            case 1:
                posKill = rand() % runners.size();
                col = runners[posKill].column;
                id = runners[posKill].idInColumn;
                organizer[col][id] = 0;
                runners.erase(runners.begin() + posKill);
                break;

            case 2:
                posKill = rand() % clippers.size();
                col = clippers[posKill].column;
                id = clippers[posKill].idInColumn;
                organizer[col][id] = 0;
                clippers.erase(clippers.begin() + posKill);
                break;
            
            case 3:
                
                break;
            
            /* case 4:
                posKill = rand() % killers.size();
                col = killers[posKill].column;
                id = killers[posKill].idInColumn;
                organizer[col][id] = 0;
                killers.erase(killers.begin() + posKill);
                break;
             */
            default:
                break;
            }

            organizer[killers[i].column][killers[i].idInColumn] = 0;
            killers.erase(killers.begin() + i);           
        }

        std::cout << "Total number of modifiers : " << runners.size() + clippers.size() + stickers.size() + killers.size() << "\n";

        window.clear();
        for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
            window.draw(grid[i]);
        window.display();

        std::this_thread::sleep_for(30ms);
    }

    return EXIT_SUCCESS;
}