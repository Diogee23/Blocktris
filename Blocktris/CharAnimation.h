#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class CharAnimation {
public:
    CharAnimation();
    bool loadSheet(const std::string& filename);

    void start(sf::Sprite& targetSprite, int animationNum);
    void update(sf::Sprite& targetSprite, int animationNum);
    bool isPlaying(int animationNum) const;
    void stop(int animationNum);

private:
    
    int frameWidth = 198;
    int frameHeight = 198;
    int totalFrames = 10;
    bool playing = false;

    sf::Texture sheet;
    int currentFrame = 0;
    int frameTimer = 0;
    
    int frameWidth2 = 297;
    int frameHeight2 = 198;
    int totalFrames2 = 27;
    bool playing2 = false;
};
