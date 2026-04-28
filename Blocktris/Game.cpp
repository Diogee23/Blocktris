#include "Game.h"

void Game::runGame()
{
    // get random seed
    srand(time(0));

    // window 
    sf::RenderWindow window(sf::VideoMode({ CELL_SIZE * COLUMNS, CELL_SIZE * ROWS }), "Blocktris");

    // initialize variables
    int lag = 0;
    int fallTimer = 0; 
    const int FALL_INTERVAL = 30; // frames betweeen each drop step 
    int lines_cleared = 0;
    std::chrono::time_point<std::chrono::steady_clock> current_time;

    Grid grid; // game grid 

    // set all the colors for the blocks
    std::vector<sf::Color> cell_colors = {
          sf::Color(36, 36, 85),    // 0 empty
          sf::Color(186, 47, 182),  // 1 T block
          sf::Color(52, 194, 233),  // 2 I block
          sf::Color(249, 154, 50),  // 3 L block 
          sf::Color(36, 86, 131),   // 4 J block 
          sf::Color(243, 71, 89),   // 5 Z block 
          sf::Color(93, 199, 71),   // 6 S block 
          sf::Color(253, 210, 67),  // 7 O block 
          sf::Color(36, 36, 36)     // 8 grid cells
    };

    // seed for random
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // spawn first block
    std::unique_ptr<Block> activeBlock = spawnBlock();

    // set current time 
    current_time = std::chrono::steady_clock::now();

    while (window.isOpen())
    {
        // get time difference between current frame and previous frame 
        int delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - current_time).count();

        // add time difference to lag 
        lag += delta_time;

        // update current time
        current_time += std::chrono::microseconds(delta_time);

        // input 
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Left)
                {
                    grid.moveBlockLeft(*activeBlock);
                }
                if (keyPressed->code == sf::Keyboard::Key::Right)
                {
                    grid.moveBlockRight(*activeBlock);
                }
                if (keyPressed->code == sf::Keyboard::Key::Down)
                {
                    grid.moveBlockDown(*activeBlock);
                }
            }
        }

        // update 
        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;
            ++fallTimer; 

            if (fallTimer >= FALL_INTERVAL)
            {
                fallTimer = 0; 
                bool moved = grid.moveBlockDown(*activeBlock);

                if (!moved)
                {
                    grid.lockBlock(*activeBlock);
                    grid.clearLine(); 
                    activeBlock = spawnBlock(); 
                }
            }
        }

        // render
        window.clear(); 

        // draw empty grid 
        float gap = 4.f;

        // create cell
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));

        // set cell color 
        cell.setFillColor(cell_colors[8]);

        // draw empty grid
        for (int a = 0; a < COLUMNS; ++a)
        {
            for (int b = 0; b < ROWS; ++b)
            {
                cell.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * a + gap / 2.f), static_cast<float>(CELL_SIZE * b + gap / 2.f)));
                window.draw(cell);
            }
        }

        // draw locked blocks 
        grid.draw(window, cell_colors); 

        // draw active block
        activeBlock->drawBlock(window, cell_colors);

        window.display();
    }
}

std::unique_ptr<Block> Game::spawnBlock()
{
    switch (std::rand() % 7)
    {
        case 0: return std::make_unique<TBlock>();
        case 1: return std::make_unique<IBlock>();
        case 2: return std::make_unique<LBlock>();
        case 3: return std::make_unique<JBlock>();
        case 4: return std::make_unique<ZBlock>();
        case 5: return std::make_unique<SBlock>();
        default: return std::make_unique<OBlock>();
    }
}