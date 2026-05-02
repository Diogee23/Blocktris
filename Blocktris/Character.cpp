#include "CharAnimation.h"

CharAnimation::CharAnimation() {}

bool CharAnimation::loadSheet(const std::string& filename)
{
    return sheet.loadFromFile(filename);
}

void CharAnimation::start(sf::Sprite& targetSprite, int animationNum)
{

    if (animationNum == 1)
    {
        playing = true;
        currentFrame = 0;
        frameTimer = 0;

        targetSprite.setTexture(sheet);

        // START ON FRAME 0
        // upset andy
        targetSprite.setTextureRect(sf::IntRect(
            sf::Vector2i(0, 0),
            sf::Vector2i(frameWidth, frameHeight)
        ));
    }
    else if (animationNum == 2)
    {
        playing2 = true;
        currentFrame = 0;
        frameTimer = 0;

        targetSprite.setTexture(sheet);

        // START ON FRAME 0
        // angry andy
        sf::IntRect rect(
            sf::Vector2i(4 * frameWidth2, 8 * frameHeight2),
            sf::Vector2i(frameWidth2, frameHeight2)
        );
    }
}

bool CharAnimation::isPlaying(int animationNum) const
{
    if (animationNum == 1)
    {
        return playing;
    }
    if (animationNum == 2)
    {
        return playing2;
    }
}

void CharAnimation::update(sf::Sprite& targetSprite, int animationNum)
{
    if(animationNum == 1)
    {
        if (!playing)
            return;

        ++frameTimer;

        if (frameTimer >= 5) // animation speed
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
    else if (animationNum == 2)
    {
        if (!playing2)
            return;

        ++frameTimer;

        if (frameTimer >= 10) // animation speed
        {
            frameTimer = 0;
            ++currentFrame;

            if (currentFrame >= totalFrames2)
            {
                playing2 = false;
                return;
            }

            int col = currentFrame % 4;
            int row = currentFrame / 4;

            sf::IntRect rect(
                sf::Vector2i(col * frameWidth2, row * frameHeight2),
                sf::Vector2i(frameWidth2, frameHeight2)
            );

            targetSprite.setTextureRect(rect);
        }
    }
}

void CharAnimation::stop(int animationNum)
{
    if (animationNum == 1)
    {
        playing = false;
        currentFrame = 0;
        frameTimer = 0;
    }
    else if (animationNum == 2)
    {
        playing2 = false;
        currentFrame = 0;
        frameTimer = 0;
    }
}
