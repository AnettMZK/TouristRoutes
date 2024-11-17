#include <iostream>
#include <SFML/Graphics.hpp>
#include "interface.h"
#include "trail.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1068, 600), "Graficar Rutas");
    Interface interface;
    Trail<sf::Vector2f>* currentTrail = nullptr;
    bool showTrail = false;

    if (!interface.loadResources()) {
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            interface.handleMouseHover(window);
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                // Verificar clic en "Crear Ruta"
                if (interface.handleCreateTrailClick(window)) {
                    std::string trailName;
                    std::cout << "Modo de creacion de ruta activado: " << std::endl;
                    std::cout << "Digite el nombre de la ruta: ";
                    std::cin >> trailName;

                    delete currentTrail;
                    currentTrail = new Trail<sf::Vector2f>(trailName);
                    showTrail = true;
                }

                if (interface.isCreatePressed() && interface.handleAddTrailClick(window)) {
                    std::cout << "Modo de agregar de ruta activado: " << interface.isAddPressed() << std::endl;
                    showTrail = true;
                }

                if (interface.isAddPressed() && currentTrail != nullptr && mousePos.x >= 0 && mousePos.x <= 900 && mousePos.y >= 0 && mousePos.y <= 600) {
                    std::string namePoint;
                    std::cout << "Digite el nombre del punto: ";
                    std::cin >> namePoint;
                    currentTrail->insert(mousePos, namePoint, interface.getCurrentColor());
                    currentTrail->printPoint();
                    showTrail = true;
                }

                // Verificar clic en "Finalizar"
                if (interface.isCreatePressed() && interface.isAddPressed() && interface.handleEndTrailClick(window)) {
                    std::cout << "Fin de ruta activado." << std::endl;
                    interface.setAddPressed(false);
                    interface.setCreatePressed(false);
                    showTrail = true;
                }

                // Verificar clic en "Guardar"
                if (interface.isEndPressed() && interface.handleSaveTrailClick(window)) {
                    showTrail = true;
                    interface.isCreatePressed();
                    if (currentTrail != nullptr) {
                        std::string filename = "SavedTrails/" + currentTrail->getName() + ".txt";
                        currentTrail->saveRouteInfo(filename);
                        std::cout << "Ruta guardada en: " << filename << std::endl;
                        currentTrail->saveTrailName("trails.txt");
                    }
                }
                
                if (interface.handleEditTrailClick(window)) {
                    std::cout << "Modo de editar de ruta activado: " << interface.isEditPressed();
                }

                // Verificar clic en "Editar" (solo edita los que estamos creando)
                if (currentTrail != nullptr && interface.isEditPressed()) {
                    std::cout << "\nSelecciona los puntos a editar" << std::endl;
                    currentTrail->selectPoint(sf::Vector2f(mousePos));
                }

                // Verificar clic en "Eliminar" (elimina una a la vez)
                if (interface.handleDeleteTrailClick(window)) {
                    std::cout << "Modo de eliminar puntos activado: " << interface.isDeletePressed();
                }

                if (currentTrail != nullptr && interface.isDeletePressed()) {
                    std::cout << "\nEliminando el punto..." << std::endl;
                    
                    std::string filename = "SavedTrails/" + currentTrail->getName() + ".txt";
                    std::cout << filename;
                    currentTrail->deletePointFromFile(filename, currentTrail->getSelectedPointName());
                    currentTrail->clearPoints();
                    currentTrail->loadTrailFromFile(filename);
                    showTrail = true;                    
                }

                // Verificar clic en "Mostrar"
                if (interface.handleShowTrailClick(window)) {
                   showTrail = false;
                   currentTrail->displayTrailNames();
                   std::string selectedTrailName;
                   std::cout << "Digite el nombre de la ruta a cargar: ";
                   std::cin >> selectedTrailName;

                   std::string filename = "SavedTrails/" + selectedTrailName + ".txt";
                   delete currentTrail; 
                   currentTrail = new Trail<sf::Vector2f>(selectedTrailName);

                   if (currentTrail->loadTrailFromFile(filename)) {
                       std::cout << "Ruta '" << selectedTrailName << "' cargada exitosamente." << std::endl;
                       showTrail = true;
                   }
                   else {
                       std::cout << "No se pudo cargar la ruta. Verifique el nombre y el archivo." << std::endl;
                       delete currentTrail;
                       currentTrail = nullptr;
                   }
                }
                // Verificar clic en "Color"
                if (interface.handleColorButtonsClick(mousePos)) {
                    std::cout << "Color cambiado" << std::endl;
                }
            }        
        }

        window.clear();
        interface.printRender(window);

        if (showTrail && currentTrail != nullptr) {
            float lineThickness = 5.0f;
            interface.drawTrailInMap(window, *currentTrail, lineThickness);
        }

        window.display();
    }
    delete currentTrail;
    return 0;
}
