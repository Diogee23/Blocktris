#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Block.h"

int main()
{
    // window 
    sf::RenderWindow window(sf::VideoMode({ CELL_SIZE * COLUMNS, CELL_SIZE * ROWS }), "Blocktris");

    // initialize variables
    int lag = 0; 
    int lines_cleared = 0; 
    std::chrono::time_point<std::chrono::steady_clock> current_time; 
    std::vector<std::vector<unsigned char>> grid(COLUMNS, std::vector<unsigned char>(ROWS)); // game grid

    // set all the colors for the cells
    std::vector<sf::Color> cell_colors = {
        sf::Color(36, 36, 85), // dark purple 0
        sf::Color(186, 47, 182), // bright purple 1
        sf::Color(52, 194, 233), // blue 2
        sf::Color(249, 154, 50), // orange 3
        sf::Color(36, 86, 131), // dark blue 4
        sf::Color(243, 71, 89), // red 5
        sf::Color(93, 199, 71), // green 6
        sf::Color(253, 210, 67), // yellow 7
        sf::Color(36, 36, 36) // grey 8
    };

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

        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;

            // add stuff here ?
        }

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close(); 
            }
        }

        if (FRAME_DURATION > lag)
        {
            float gap = 4.f;

            // create cell
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - gap, CELL_SIZE - gap));

            // create border 
            sf::RectangleShape border(sf::Vector2f(5 * CELL_SIZE, 5 * CELL_SIZE));

            // set border visuals
            border.setFillColor(sf::Color(0, 0, 0));
            border.setOutlineThickness(-1);
            border.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * (1.5f * COLUMNS - 2.5f)), static_cast<float>(CELL_SIZE * (0.25f * ROWS - 2.5f))));

            // clear window from previous frame
            window.clear();

            // set cell color 
            cell.setFillColor(cell_colors[8]);

            // draw the blocktris screen
            for (int a = 0; a < COLUMNS; ++a)
            {
                for (int b = 0; b < ROWS; ++b)
                {
                    cell.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * a + gap / 2.f), static_cast<float>(CELL_SIZE * b + gap / 2.f)));
                    window.draw(cell);
                }
            }

            window.display();
        }
    }
}