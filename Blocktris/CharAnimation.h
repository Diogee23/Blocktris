#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class CharAnimation {
public:
    CharAnimation();
    bool loadSheet(const std::string& filename);

    void start(sf::Sprite& targetSprite);
    void update(sf::Sprite& targetSprite);
    bool isPlaying() const;


private:
    sf::Texture sheet;
    int frameWidth = 198;
    int frameHeight = 198;
    int totalFrames = 10;

    int currentFrame = 0;
    int frameTimer = 0;
    bool playing = false; //

    sf::Texture angered_sheet;
    int frameWidth2 = 1188;
    int frameHeight2 = 1188;
    int totalFrames2 = 27;

    int currentFrame2 = 0;
    int frameTimer2 = 0;
    bool playing2 = false; //wrath_of_andy

	// sf::Texture angered_sheet;
	// int frameWidth3 = 990;
	// int frameHeight3 = 1188;
	// int totalFrames3 = 27;

	// int currentFrame3 = 0;
	// int frameTimer3 = 0;
	// bool teehee = false;
};
