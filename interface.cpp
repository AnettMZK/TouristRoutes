#pragma once
#include "interface.h"

Interface::Interface() : addIsPressedFlag(false), createIsPressedFlag(false), endIsPressedFlag(false), showIsPressedFlag(false), editIsPressedFlag(true), deleteIsPressedFlag(true)
{  
    //Botones de colores 
    colorPowderBlue.setSize(sf::Vector2f(30, 30));
    colorPowderBlue.setFillColor(sf::Color(190, 233, 232));
    colorPowderBlue.setPosition(940.8f, 475.7f);

    colorSkyBlue.setSize(sf::Vector2f(30, 30));
    colorSkyBlue.setFillColor(sf::Color(98, 182, 203));
    colorSkyBlue.setPosition(985.7f, 475.7f);

    colorSteelBlue.setSize(sf::Vector2f(30, 30));
    colorSteelBlue.setFillColor(sf::Color(42, 97, 130));
    colorSteelBlue.setPosition(1030.5, 475.7f);

    colorLightCyan.setSize(sf::Vector2f(30, 30));
    colorLightCyan.setFillColor(sf::Color(224, 242, 255));
    colorLightCyan.setPosition(940.8f, 514.4f);

    colorFlowerBlue.setSize(sf::Vector2f(30, 30));
    colorFlowerBlue.setFillColor(sf::Color(95, 168, 211));
    colorFlowerBlue.setPosition(985.7f, 514.4f);

    colorTeal.setSize(sf::Vector2f(30, 30));
    colorTeal.setFillColor(sf::Color(54, 115, 128));
    colorTeal.setPosition(1030.5f, 514.4f);
}

bool Interface::loadResources()
{
    if (!mapTexture.loadFromFile("oahuMap.png")) {
        std::cerr << "Error al cargar la imagen Mapa." << std::endl;
        return false;
    }

    mapSprite.setTexture(mapTexture);

    if (!PlayfairDisplay.loadFromFile("PlayfairDisplay.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return false;
    }

    initializeButtons(createTrailRect, createTrailText, 938.8f, 111.3f, 117.7f, 31.7f, "Crear Ruta", PlayfairDisplay);
    initializeButtons(addButtonRect, addButtonText, 938.8f, 155.9f, 117.7f, 31.7f, "Agregar", PlayfairDisplay);
    initializeButtons(endTrailRect, endTrailText, 938.8f, 199.0f, 117.7f, 31.7f, "Finalizar", PlayfairDisplay);
    initializeButtons(saveTrailRect, saveTrailText, 938.8f, 242.3f, 117.7f, 31.7f, "Guardar", PlayfairDisplay);
    initializeButtons(editTrailRect, editTrailText, 938.8f, 284.2f, 117.7f, 31.7f, "Editar", PlayfairDisplay);
    initializeButtons(deleteTrailRect, deleteTrailText, 938.8f, 327.8f, 117.7f, 31.7f, "Eliminar", PlayfairDisplay);
    initializeButtons(showTrailRect, showTrailText, 938.8f, 372.5f, 117.7f, 31.7f, "Mostrar", PlayfairDisplay);

    return true;
}

void Interface::initializeButtons(sf::RectangleShape& rect, sf::Text& text, float posX, float posY, float width, float height, const std::string& buttonText, sf::Font& font)
{
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color(32, 77, 85));
    rect.setPosition(posX, posY);
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    if (rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        rect.setFillColor(sf::Color(63, 124, 134));
    }

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(223, 228, 214));

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(
        rect.getPosition().x + rect.getSize().x / 2,
        rect.getPosition().y + rect.getSize().y / 2
    );
}

void Interface::handleMouseHover(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (createTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        createTrailRect.setFillColor(sf::Color(63, 124, 134)); 
    }
    else {
        createTrailRect.setFillColor(sf::Color(32, 77, 85)); 
    }

    if (addButtonRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        addButtonRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        addButtonRect.setFillColor(sf::Color(32, 77, 85));
    }

    if (endTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        endTrailRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        endTrailRect.setFillColor(sf::Color(32, 77, 85));
    }

    if (saveTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        saveTrailRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        saveTrailRect.setFillColor(sf::Color(32, 77, 85));
    }

    if (editTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        editTrailRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        editTrailRect.setFillColor(sf::Color(32, 77, 85));
    }

    if (deleteTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        deleteTrailRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        deleteTrailRect.setFillColor(sf::Color(32, 77, 85));
    }

    if (showTrailRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        showTrailRect.setFillColor(sf::Color(63, 124, 134));
    }
    else {
        showTrailRect.setFillColor(sf::Color(32, 77, 85));
    }
}
void Interface::printRender(sf::RenderWindow& window)
{
    window.draw(mapSprite);

    window.draw(createTrailRect);
    window.draw(createTrailText);
    window.draw(addButtonRect);
    window.draw(addButtonText);
    window.draw(endTrailRect);
    window.draw(endTrailText);
    window.draw(saveTrailRect);
    window.draw(saveTrailText);
    window.draw(editTrailRect);
    window.draw(editTrailText);
    window.draw(deleteTrailRect);
    window.draw(deleteTrailText);
    window.draw(showTrailRect);
    window.draw(showTrailText);

    window.draw(colorPowderBlue);
    window.draw(colorSkyBlue);
    window.draw(colorSteelBlue);
    window.draw(colorLightCyan);
    window.draw(colorFlowerBlue);
    window.draw(colorTeal);
}

bool Interface::handleAddTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (addButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        addIsPressedFlag = !addIsPressedFlag;
        editIsPressedFlag = false;
        deleteIsPressedFlag = false;
        return true;
    }
    return false;
}

bool Interface::handleCreateTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (createTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        createIsPressedFlag = !createIsPressedFlag;
        editIsPressedFlag = false;
        deleteIsPressedFlag = false;
        return true;
    }
    return false;
}

bool Interface::handleEndTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (endTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        addIsPressedFlag = false;
        endIsPressedFlag = true;
        createIsPressedFlag = false;
        editIsPressedFlag = false;
        deleteIsPressedFlag = false;
        return true;
    }
    return false;
}

bool Interface::handleSaveTrailClick(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (saveTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        editIsPressedFlag = false;
        return true; 
    }
    return false;
}

bool Interface::handleShowTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (showTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        showIsPressedFlag = !showIsPressedFlag;
        editIsPressedFlag = false;
        deleteIsPressedFlag = false;
        return true;
    }
    return false;
}

bool Interface::handleColorButtonsClick(const sf::Vector2f& mousePos)
{
    if (colorFlowerBlue.getGlobalBounds().contains(mousePos)) {
        currentColor = sf::Color(190, 233, 232);
        return true;
    }
    else if (colorSkyBlue.getGlobalBounds().contains(mousePos)) {
        currentColor = sf::Color(98, 182, 203);
        return true;
    }
    else if (colorSteelBlue.getGlobalBounds().contains(mousePos)) {
        currentColor = sf::Color(42, 97, 130);
        return true;
    }
    else if (colorLightCyan.getGlobalBounds().contains(mousePos)) {
        currentColor = sf::Color(224, 242, 255);
        return true;
    }
    else if (colorTeal.getGlobalBounds().contains(mousePos)) {
        currentColor = sf::Color(54, 115, 128);
        return true;
    }
    return false;
}

bool Interface::handleEditTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (editTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        editIsPressedFlag = !editIsPressedFlag;
        deleteIsPressedFlag = false;
        return true;
    }
    return false;
}

bool Interface::handleDeleteTrailClick(const sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (deleteTrailRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        deleteIsPressedFlag = !deleteIsPressedFlag;
        editIsPressedFlag = false;
        return true;
    }
    return false;
}

void Interface::drawTrailInMap(sf::RenderWindow& window, const Trail<sf::Vector2f>& trail, float lineThickness)
{
    trail.createLine(window, lineThickness);
    trail.drawPoints(window, PlayfairDisplay);
}

bool Interface::isAddPressed()
{
    return addIsPressedFlag;
}

bool Interface::isEditPressed()
{
    return editIsPressedFlag;
}

bool Interface::isCreatePressed()
{
    return createIsPressedFlag;
}

bool Interface::isShowPressed()
{
    return showIsPressedFlag;
}

void Interface::setAddPressed(bool value)
{
    addIsPressedFlag = value;
}

void Interface::setCreatePressed(bool value)
{
   createIsPressedFlag = value;

}

bool Interface::isEndPressed()
{
    return endIsPressedFlag;
}

bool Interface::isDeletePressed()
{
    return deleteIsPressedFlag;
}

sf::Color Interface::getCurrentColor(){
    return currentColor;
}