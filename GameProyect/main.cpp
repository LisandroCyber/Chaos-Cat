#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Personaje.h"
#include "ObjetoChico.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Chaos Cat SFML 3");
    window.setFramerateLimit(144);

    sf::Texture texturaFondo;
    if (!texturaFondo.loadFromFile("images/fondo.jpg"))
    {
        std::cout << "Error al cargar la imagen de fondo!" << std::endl;
        return -1;
    }
    sf::Sprite spriteFondo(texturaFondo);

    Personaje gato;
    ObjetoChico taza;

    bool tocandoTaza = false;
    bool mostrarHitboxes = true; // DEBUG HITBOXES: cambiar a true para mostrarlos

    while (window.isOpen()) {
       
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        gato.update();

        const sf::FloatRect areaTaza = taza.getGlobalBounds();
        sf::FloatRect areaGato = gato.getGlobalBounds();

        if (areaGato.findIntersection(areaTaza))
        {
            if (!tocandoTaza)
            {
                std::cout << "TIRAR TAZA" << std::endl;
                tocandoTaza = true;
            }

            float dx1 = areaTaza.position.x - (areaGato.position.x + areaGato.size.x);
            float dx2 = (areaTaza.position.x + areaTaza.size.x) - areaGato.position.x;
            float dy1 = areaTaza.position.y - (areaGato.position.y + areaGato.size.y);
            float dy2 = (areaTaza.position.y + areaTaza.size.y) - areaGato.position.y;

            float dx = (std::abs(dx1) < std::abs(dx2)) ? dx1 : dx2;
            float dy = (std::abs(dy1) < std::abs(dy2)) ? dy1 : dy2;

            if (std::abs(dx) < std::abs(dy))
            {
                gato.mover({ dx, 0.f });
            }
            else
            {
                gato.mover({ 0.f, dy });
            }
        }
        else
        {
            tocandoTaza = false;
        }

        window.clear(); 
        window.draw(spriteFondo);

        window.draw(gato);         
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
            std::cout << "Posision en x: " << gato.getPosx() << std::endl;
            std::cout << "Posision en y: " << gato.getPosy() << std::endl;
        }
        
        window.draw(taza);

        // DEBUG HITBOXES: gato en verde, taza en rojo.
        if (mostrarHitboxes)
        {
            const sf::FloatRect hitboxGato = gato.getGlobalBounds();
            sf::RectangleShape rectGato(hitboxGato.size);
            rectGato.setPosition(hitboxGato.position);
            rectGato.setFillColor(sf::Color::Transparent);
            rectGato.setOutlineColor(sf::Color::Green);
            rectGato.setOutlineThickness(2.f);

            const sf::FloatRect hitboxTaza = taza.getGlobalBounds();
            sf::RectangleShape rectTaza(hitboxTaza.size);
            rectTaza.setPosition(hitboxTaza.position);
            rectTaza.setFillColor(sf::Color::Transparent);
            rectTaza.setOutlineColor(sf::Color::Red);
            rectTaza.setOutlineThickness(2.f);

            window.draw(rectGato);
            window.draw(rectTaza);
        }
      
        window.display(); 
    }

    return 0;
}
