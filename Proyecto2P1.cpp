#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "trail.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1068, 600), "Graficar Rutas");
    Interface interface;
    Trail<sf::Vector2f>* currentTrail = nullptr;

    if (!interface.loadResources()) {
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                if (interface.handleCreateTrailClick(window)) {
                    std::string trailName;
                    std::cout << "Modo de creacion de ruta activado: " << std::endl;
                    std::cout << "Digite el nombre de la ruta: ";
                    std::getline(std::cin >> std::ws, trailName);
             
                    delete currentTrail;
                    currentTrail = new Trail<sf::Vector2f>(trailName);
                   
                }

                if (interface.isCreatePressed() && interface.handleAddTrailClick(window)) {
                    std::cout << "Modo de agregar de ruta activado: " << interface.isAddPressed() << std::endl;
                }

                if (interface.isAddPressed() && currentTrail != nullptr && mousePos.x >= 0 && mousePos.x <= 900 && mousePos.y >= 0 && mousePos.y <= 600) {
                    std::string namePoint;
                    std::cout << "Digite el nombre del punto: ";
                    std::getline(std::cin >> std::ws, namePoint);
                    
                    currentTrail->insert(mousePos, namePoint, interface.getCurrentColor());
                    currentTrail->printPoint();
                }

                if (interface.isCreatePressed() && interface.isAddPressed() && interface.handleEndTrailClick(window)) {
                    std::cout << "Fin de ruta activado." << std::endl;
                    interface.setAddPressed(false);
                    interface.setCreatePressed(false);
                }


                if (interface.isEndPressed() && interface.handleSaveTrailClick(window)) {

                    interface.isCreatePressed();
                    if (currentTrail != nullptr) {
                        std::string filename = "SavedTrails/" + currentTrail->getName() + ".txt";
                        currentTrail->saveRouteInfo(filename);
                        std::cout << "Ruta guardada en: " << filename << std::endl;
                        currentTrail->saveTrailName("trails.txt");
                    }
                    
                }

                if (interface.handleShowTrailClick(window)) {
                   currentTrail->displayTrailNames();
                }
                if (interface.handleColorButtonsClick(mousePos)) {
                    std::cout << "Color cambiado" << std::endl; 
                }
            }        
        }

        window.clear();
        interface.printRender(window);

        if (currentTrail != nullptr) {
            float lineThickness = 5.0f;
            interface.drawTrailInMap(window, *currentTrail, lineThickness);
        }

        window.display();
    }
    delete currentTrail;
    return 0;
}