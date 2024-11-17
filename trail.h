#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

template <typename T>

class Trail {
private:
    struct Node {
        T data;
        std::string namePoint;
        Node* next;
        Node* previous;
        sf::Color color;
        Node(T value, std::string namePoint, sf::Color color) : data(value), namePoint(namePoint), color(color),next(nullptr), previous(nullptr) {}
    };
    std::string nameTrail;
    std::string selectedPointName;
    Node* head;
    Node* tail;
public:
    Trail(std::string nameTrail) : nameTrail(nameTrail), selectedPointName(""), head(nullptr), tail(nullptr) {}

    Node* getHead() {
        return head;
    }

    void insert(T& value, std::string name, sf::Color currentColor) {
        Node* freshNode = new Node(value, name, currentColor);

        if (head == nullptr) {
            head = freshNode;
            tail = freshNode;
        }
        else {
            freshNode->previous = tail;
            tail->next = freshNode;
            tail = freshNode;
        }
    }

    void drawPoints(sf::RenderWindow& window, const sf::Font& font) const {
        Node* current = head;
        while (current != nullptr) {
            sf::CircleShape point(7.0f);
            point.setOrigin(7.0f, 7.0f);
            point.setPosition(current->data);
            point.setFillColor(current->color);
            window.draw(point);

            sf::Text nodeName;
            nodeName.setFont(font);
            nodeName.setString(current->namePoint);
            nodeName.setCharacterSize(16);
            nodeName.setFillColor(sf::Color(115, 115, 115));
            nodeName.setPosition(current->data.x + 10, current->data.y - 10);

            window.draw(nodeName);

            current = current->next;
        }
    }

    void selectPoint(const sf::Vector2f& mousePos) {
        Node* current = head;

        while (current != nullptr) {
            sf::CircleShape point(7.0f);
            point.setOrigin(7.0f, 7.0f);
            point.setPosition(current->data);

            if (point.getGlobalBounds().contains(mousePos)) {
                current->color = sf::Color::Red;
                selectedPointName = current->namePoint;
                break;
            }
            current = current->next;
        }
            if(current!=nullptr){
                std::cout << current->namePoint << ": (" << current->data.x << ", " << current->data.y << ")" << std::endl;                
            }
    }


    void createLine(sf::RenderWindow& window, float thickness) const {
        Node* current = head;

        while (current != nullptr && current->next != nullptr) {
            sf::Vector2f start = current->data;
            sf::Vector2f end = current->next->data;
            sf::Vector2f direction = end - start;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159265f;

            sf::RectangleShape line(sf::Vector2f(length, thickness));
            line.setPosition(start);
            line.setRotation(angle);
            line.setFillColor(sf::Color(190, 233, 232));

            window.draw(line);

            current = current->next;
        }
    }

    void printPoint() {
        if (tail != nullptr) {
            std::cout << tail->namePoint << ": (" << tail->data.x << ", " << tail->data.y << ")" << std::endl;
        }
    }

    void printAllPoints() {
        Node* current = head;
        if (!current) {
            std::cout << "La lista esta vacia." << std::endl;
            return;
        }

        while (current != nullptr) {
            std::cout << current->namePoint << ": (" << current->data.x << ", " << current->data.y << ")" << std::endl;
            current = current->next;
        }
    }

    void setName(std::string& newName) {
        nameTrail = newName;
    }

    std::string getName() {
        return nameTrail;
    }

    void saveTrailName(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app); 
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar el nombre de la ruta: " << filename << std::endl;
            return;
        }

        file << nameTrail << std::endl; 
        file.close();
    }
    
    void displayTrailNames() {
        std::ifstream file("trails.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo: trails.txt" << std::endl;
            return;
        }

        std::string line;
        system("cls");
        std::cout << "Rutas disponibles:" << std::endl;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }

    void saveRouteInfo(const std::string& filename) {
        std::ofstream file(filename, std::ios::out);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar la ruta: " << filename << std::endl;
            return;
        }

        file << "Ruta: " << nameTrail << "\n";
        Node* current = head;
        int pointIndex = 1;

        while (current != nullptr) {
            file << pointIndex << "." << current->namePoint << ":("
                << current->data.x << ", " << current->data.y << ")\n";
            current = current->next;
            pointIndex++;
        }
        file.close();
    }

    bool loadTrailFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo: " << filename << std::endl;
            return false;
        }

        std::string line;
        std::getline(file, line);
        std::string tempNameTrail = line.substr(6); 

        while (std::getline(file, line)) {
            std::size_t posStart = line.find(":(");
            std::size_t posEnd = line.find(")", posStart);

            if (posStart != std::string::npos && posEnd != std::string::npos) {
                std::string namePoint = line.substr(line.find('.') + 1, posStart - line.find('.') - 1);
                std::string coords = line.substr(posStart + 2, posEnd - posStart - 2);
                std::istringstream coordStream(coords);
                float x, y;
                char comma;
                coordStream >> x >> comma >> y;

                T position(x, y);
                sf::Color color = sf::Color::White; 
                insert(position, namePoint, color);
            }
        }

        file.close();
        if (head == nullptr) {
            std::cout << "Error: la lista de puntos esta vacia despues de cargar la ruta." << std::endl;
            return false;
        }
        return true;
    }

    void deletePointFromFile(const std::string& filename, const std::string& pointName) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
            return;
        }

        std::string line;
        std::ostringstream buffer;
        bool pointDeleted = false;

        while (std::getline(file, line)) {
            size_t pos = line.find(".");
            if (pos != std::string::npos) {
                std::string name = line.substr(pos + 1, line.find(":") - pos - 1); 
                if (name == pointName) {
                    pointDeleted = true;
                }
                else {
                    buffer << line << std::endl;
                }
            }
            else {
                buffer << line << std::endl;
            }
        }

        file.close();

        if (pointDeleted) {
            std::ofstream outFile(filename);
            if (!outFile.is_open()) {
                std::cerr << "No se pudo abrir el archivo para actualizar: " << filename << std::endl;
                return;
            }

            outFile << buffer.str();
            outFile.close();
            std::cout << "Punto eliminado del archivo " << filename << std::endl;
        }
        else {
            std::cout << "No se encontro el punto: " << pointName << std::endl;
        }
    }


    void clearPoints() {
        while (head != nullptr) {
            Node* nextPoint = head->next;
            delete head;
            head = nextPoint;
        }
        tail = nullptr;
    }

    std::string getSelectedPointName() {
        return selectedPointName;
    }

    ~Trail() {
        while (head != nullptr) {
            Node* nextNode = head->next;
            delete head;
            head = nextNode;
        }
        tail = nullptr;
    }
};