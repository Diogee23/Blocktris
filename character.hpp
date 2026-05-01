#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
    Character();  // we will construct sprite correctly here
    std::optional<sf::Sprite> sprite;  // Sprite cannot be default-constructed

    bool load(const std::string& filename);
    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture texture;
};
