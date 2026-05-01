#include "CharAnimation.hpp"

CharAnimation::CharAnimation() {}

bool CharAnimation::loadSheet(const std::string& filename)
{
    return sheet.loadFromFile(filename);
}

void CharAnimation::start(sf::Sprite& targetSprite)
{
    playing = true;
    currentFrame = 0;
    frameTimer = 0;

    targetSprite.setTexture(sheet);

    // ⭐ START ON FRAME 0
    targetSprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(frameWidth, frameHeight)
    ));
}

bool CharAnimation::isPlaying() const
{
    return playing;
}

void CharAnimation::update(sf::Sprite& targetSprite)
{
    if (!playing)
        return;

    ++frameTimer;

    if (frameTimer >= 15) // animation speed
    {
        frameTimer = 0;
        ++currentFrame;

        if (currentFrame >= totalFrames)
        {
            playing = false;
            return;
        }

        // compute row/column
        int col = currentFrame % 3;
        int row = currentFrame / 3;

        sf::IntRect rect(
            sf::Vector2i(col * frameWidth, row * frameHeight),
            sf::Vector2i(frameWidth, frameHeight)
        );

        targetSprite.setTextureRect(rect);
    }
}