#pragma once
#include <SFML/Graphics.hpp>
#include "trail.h"
#include <iostream>

class Interface
{
private:
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::Font PlayfairDisplay;

    sf::RectangleShape addButtonRect;
    sf::RectangleShape createTrailRect;
    sf::RectangleShape endTrailRect;
    sf::RectangleShape saveTrailRect;
    sf::RectangleShape showTrailRect;
    sf::RectangleShape editTrailRect;
    sf::RectangleShape deleteTrailRect;

    sf::RectangleShape colorPowderBlue;
    sf::RectangleShape colorSkyBlue;
    sf::RectangleShape colorSteelBlue;
    sf::RectangleShape colorLightCyan;
    sf::RectangleShape colorFlowerBlue;
    sf::RectangleShape colorTeal;

    sf::Text addButtonText;
    sf::Text createTrailText;
    sf::Text endTrailText;
    sf::Text saveTrailText;
    sf::Text showTrailText;
    sf::Text editTrailText;
    sf::Text deleteTrailText;
    sf::Color currentColor = sf::Color(72, 128, 140); 

    bool addIsPressedFlag;
    bool createIsPressedFlag;
    bool endIsPressedFlag;
    bool showIsPressedFlag;

public:

    Interface();
    void initializeColorButtons(sf::RectangleShape& button, const sf::Color& color, float posX, float posY);
    bool loadResources();
    void initializeButtons(sf::RectangleShape& rect, sf::Text& text, float posX, float posY, float width, float height, const std::string& buttonText, sf::Font& font);
    void printRender(sf::RenderWindow& window);
    bool handleAddTrailClick(const sf::RenderWindow& window);
    bool handleCreateTrailClick(const sf::RenderWindow& window);
    bool handleEndTrailClick(const sf::RenderWindow& window);
    bool handleSaveTrailClick(const sf::RenderWindow& window);
    bool handleShowTrailClick(const sf::RenderWindow& window);
    bool handleColorButtonsClick(const sf::Vector2f& mousePos);
    void drawTrailInMap(sf::RenderWindow& window, const Trail<sf::Vector2f>& trail, float lineThickness);
    bool isAddPressed();
    bool isCreatePressed();
    bool isShowPressed();
    bool endClicked();
    void setAddPressed(bool value);
    void setCreatePressed(bool value);
    bool isEndPressed();
    sf::Color getCurrentColor();

};

