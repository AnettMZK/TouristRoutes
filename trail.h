#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
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
        Node(T value, std::string namePoint, sf::Color color) : data(value), namePoint(namePoint), color(color), next(nullptr), previous(nullptr) {}
    };
    std::string nameTrail;
    Node* head;
    Node* tail;


public:
    Trail(std::string nameTrail) : nameTrail(nameTrail), head(nullptr), tail(nullptr) {}

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

            // Dibujar siempre el nombre del punto
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


    void clearPoints() {
        while (head != nullptr) {
            Node* nextPoint = head->next;
            delete head;
            head = nextPoint;
        }
        tail = nullptr;
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