#include "Game.h"

void Game::runGame()
{
    // get random seed
    srand(time(0));

    // window 
    sf::RenderWindow window(sf::VideoMode({ CELL_SIZE * COLUMNS + SIDEBAR_WIDTH, CELL_SIZE * ROWS }), "Blocktris");

    // bring game window to front
    HWND hwnd = window.getNativeHandle();
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 

    // initialize variables
    int lag = 0;
    int fallTimer = 0; 
    const int FALL_INTERVAL = 30; // frames betweeen each drop step 
    int temp_fallSpd = FALL_INTERVAL;
    int lines_cleared = 0;
    int level = 1; // level corresponds to the speed - increments every 10 lines cleared
    int currentFallSpd = FALL_INTERVAL;
    std::chrono::time_point<std::chrono::steady_clock> current_time;

    Grid grid; // game grid 

    // flash state
    std::vector<int> flashRows;
    int flashTimer = 0;
    const int FLASH_DURATION = 10;

    // set all the colors for the blocks
    std::vector<sf::Color> cell_colors = {
          sf::Color(36, 36, 85),    // 0 empty
          sf::Color(186, 47, 182),  // 1 T block (purple)
          sf::Color(52, 194, 233),  // 2 I block (light blue)
          sf::Color(249, 154, 50),  // 3 L block (orange)
          sf::Color(36, 86, 131),   // 4 J block (dark blue) 
          sf::Color(243, 71, 89),   // 5 Z block (red)
          sf::Color(93, 199, 71),   // 6 S block (green)
          sf::Color(253, 210, 67),  // 7 O block (yellow)
          sf::Color(36, 36, 36)     // 8 grid cells (gray)
    };

    // seed for random
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // spawn first block
    std::unique_ptr<Block> activeBlock = spawnBlock();
    std::unique_ptr<Block> nextBlock = spawnBlock();
	checkGameOver(grid, *activeBlock);

    // set current time 
    current_time = std::chrono::steady_clock::now();

    // add in text font 
    sf::Font font; 
    font.openFromFile("comic.ttf");

    // add in music
    sf::Music music;
    music.openFromFile("blocktris.mp3");

    // play music
    music.play();

    // add in pop sound effect
    sf::SoundBuffer buffer;
    buffer.loadFromFile("pop.mp3");
    sf::Sound sound(buffer);

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
				if (keyPressed->code == sf::Keyboard::Key::X)
				{
					grid.rotateBlock(*activeBlock);
				}
                if (keyPressed->code == sf::Keyboard::Key::Z)
				{
					grid.rotateBlockCounter(*activeBlock);
				}
                if (keyPressed->code == sf::Keyboard::Key::Up)
                {
                    grid.hardDrop(*activeBlock);
                }
            }
        }

        // update 
        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

            if (isGameOver) // tick grey effect every frame when game is over
            {
                ++greyTimer;

                if (greyTimer >= 5 && greyRow > 0)   // adjust effect speed here
                {
                    --greyRow;
                    greyTimer = 0;
                }
            }
            else if (flashTimer > 0) // adjust flashTimer every frame while game not over
            {
                --flashTimer;

                if (flashTimer == 0)
                {
                    // clear lines and reset flashRows 
                    lines_cleared += grid.clearLine();
                    flashRows.clear();

                    // play pop sound effect
                    sound.play();

                    // adjust fall speed based on lines cleared
                    currentFallSpd = std::max(5, FALL_INTERVAL - (lines_cleared / 5) * 2);

                    // increment level every 5 lines
                    level = 1 + (lines_cleared / 5);

                    // set new active block and next block 
                    activeBlock = std::move(nextBlock);
                    nextBlock = spawnBlock();
                    checkGameOver(grid, *activeBlock);
                }
            }
            else // only move/lock when not flashing 
            {
                ++fallTimer;

                if (fallTimer >= currentFallSpd)
                {
                    bool moved = grid.moveBlockDown(*activeBlock);
                    fallTimer = 0;

                    if (!moved)
                    {
                        // check if block is in a valid position
                        if (grid.isValidPosition(*activeBlock))
                        {
                            // if yes, lock the block in place 
                            grid.lockBlock(*activeBlock);
                            flashRows = grid.getFullRows();

                            // set up for flash effect 
                            if (!flashRows.empty())
                            {
                                flashTimer = FLASH_DURATION;
                            }
                            else
                            {
                                // stops spawn after the block locks
                                checkGameOver(grid, *activeBlock);

                                if (!isGameOver)
                                {
                                    activeBlock = std::move(nextBlock);
                                    nextBlock = spawnBlock();
                                }
                            }
                        }
                        else if ((*activeBlock).getPosition()[1].y >= 0)
                        {
                            grid.bounceBlock(*activeBlock);
                        }
                    }
                }
            }   
        }

        // render
        window.clear(); 
        float gap = 4.f;

        // create cells
        sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));
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
        grid.draw(window, cell_colors, isGameOver, greyRow);

        // flash full lines 
        if (flashTimer > 0)
        {
            int alpha = (flashTimer % 2 == 0) ? 200.f : 0.f;
            sf::RectangleShape flashCell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));
            flashCell.setFillColor(sf::Color(255, 255, 255, static_cast<unsigned char>(alpha)));

            for (int row : flashRows)
            {
                for (int col = 0; col < COLUMNS; ++col)
                {
                    flashCell.setPosition(sf::Vector2f(col * CELL_SIZE + gap / 2.f, row * CELL_SIZE + gap / 2.f));
                    window.draw(flashCell);
                }
            }
        }

        // draw active block (only while the game is not over and there's no flash effect) 
        if (!isGameOver && flashTimer == 0)
        {
            activeBlock->drawBlock(window, cell_colors);
        }

        // draw sidebar background 
        sf::RectangleShape sidebar(sf::Vector2f(SIDEBAR_WIDTH, CELL_SIZE * ROWS));
        sidebar.setFillColor(sf::Color::Black); 
        sidebar.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * COLUMNS), 0.f)); 
        window.draw(sidebar); 

        // draw preview window 
        sf::RectangleShape preview_window(sf::Vector2f(460.f, 460.f)); 
        preview_window.setFillColor(sf::Color::White); 
        preview_window.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * COLUMNS + 20.f), 20.f));
        window.draw(preview_window); 

        // draw next block preview
        nextBlock->drawPreviewBlock(window, cell_colors, isGameOver, greyRow);

        // draw lines cleared label 
        sf::Text lines_label(font, "Lines Cleared: ", 40); 
        lines_label.setFillColor(sf::Color::White); 
        lines_label.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * COLUMNS + 20.f), 510.f));
        window.draw(lines_label); 

        // draw lines cleared count 
        sf::Text line_count(font, std::to_string(lines_cleared), 40);
        line_count.setFillColor(sf::Color::White);
        line_count.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * COLUMNS + 20.f + lines_label.getLocalBounds().size.x), 510.f));
        window.draw(line_count);

        // draw level label 
        sf::Text level_label(font, "Level: ", 40);
        level_label.setFillColor(sf::Color::White);
        level_label.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE* COLUMNS + 20.f), 570.f));
        window.draw(level_label);

        // draw lines cleared count 
        sf::Text level_count(font, std::to_string(level), 40);
        level_count.setFillColor(sf::Color::White);
        level_count.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE* COLUMNS + 20.f + level_label.getLocalBounds().size.x), 570.f));
        window.draw(level_count);

        // if the game is over 
        if (isGameOver && greyRow == 0)
        {
            // draw gameover window 
            sf::RectangleShape gameover_window(sf::Vector2f(440.f, 440.f));
            gameover_window.setFillColor(sf::Color(50, 50, 50));
            gameover_window.setPosition(sf::Vector2f(static_cast<float>((CELL_SIZE* COLUMNS) / 2 - 220), 
                static_cast<float>((CELL_SIZE* ROWS) / 2 - 220)));
            window.draw(gameover_window);

            sf::Text game_label(font, "GAME", 120);
            game_label.setFillColor(sf::Color(170, 0, 0));
            game_label.setPosition(sf::Vector2f(static_cast<float>((CELL_SIZE * COLUMNS) / 2 - 180), 
                static_cast<float>((CELL_SIZE * ROWS) / 2 - 160)));
            window.draw(game_label);

            sf::Text over_label(font, "OVER", 120);
            over_label.setFillColor(sf::Color(170, 0, 0));
            over_label.setPosition(sf::Vector2f(static_cast<float>((CELL_SIZE * COLUMNS) / 2 - 170), 
                static_cast<float>((CELL_SIZE * ROWS) / 2)));
            window.draw(over_label);
        }

        window.display();
    }
}

void Game::checkGameOver(const Grid& grid, const Block& block)
{
	// If the new block cannot be placed game over
	if (grid.isTopReached())
	{
		isGameOver = true;
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