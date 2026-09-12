#include <SFML/Graphics.hpp>
#include "ObjetoChico.h"
#include <iostream>

sf::Texture ObjetoChico::cargarTextura()
{
	sf::Texture textura;

	if (!textura.loadFromFile("images/TazaCafe.png"))
	{
		std::cout << "ERROR: NO SE PUDO CARGAR LA TAZA  ";
		exit(-1);
	}

	return textura;
}

ObjetoChico::ObjetoChico() : _texture(cargarTextura()), _sprite(_texture)
{
	_sprite.setPosition({  458.f, 478.f });
	_sprite.setScale({ 0.2f, 0.2f });
	_sprite.setOrigin({ _sprite.getGlobalBounds().size.x / 2, 0 });
	_peso = 0.5f;
	_ruido = 0.5f;
	_dificultad = 1.f;
}

void ObjetoChico::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

sf::FloatRect ObjetoChico::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}