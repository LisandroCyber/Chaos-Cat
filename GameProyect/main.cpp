#include <SFML/Graphics.hpp>
#include <iostream>
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
 

    while (window.isOpen()) {
       
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(); 
        window.draw(spriteFondo);
        
        gato.update();

        window.draw(gato);         
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
            std::cout << "Posision en x: " << gato.getPosx() << std::endl;
            std::cout << "Posision en y: " << gato.getPosy() << std::endl;
        }
        
        window.draw(taza);
      
        window.display(); 
    }

    return 0;
}