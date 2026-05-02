#include "Character.h"

Character::Character()
{
    // sprite will be created AFTER texture loads
}

bool Character::load(const std::string& filename)
{
    if (!texture.loadFromFile(filename))
        return false;

    // NOW we can construct the sprite legally
    sprite.emplace(texture);

    return true;
}

void Character::setPosition(const sf::Vector2f& pos)
{
    if (sprite.has_value())
        sprite->setPosition(pos);
}

void Character::draw(sf::RenderWindow& window) const
{
    if (sprite.has_value())
        window.draw(*sprite);
}
