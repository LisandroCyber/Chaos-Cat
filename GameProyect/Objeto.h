#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Objeto
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _posicionInicial;
	sf::Vector2f _velocidad;
	bool _tirado;
	bool _visible;
	
	static sf::Texture cargarTextura(const std::string& rutaTextura);

public:
	
	Objeto(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala);

	sf::FloatRect getGlobalBounds() const;
	void update();
	void tirar(float direccion);
	void reiniciar();
	bool estaTirado() const;

	void dibujar(sf::RenderWindow& ventana) const;
};
