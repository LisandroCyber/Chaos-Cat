#include <SFML/Graphics.hpp>
#include "ObjetoChico.h"
#include <cstdlib>
#include <iostream>

sf::Texture ObjetoChico::cargarTextura(const std::string& rutaTextura)
{
	sf::Texture textura;

	if (!textura.loadFromFile(rutaTextura))
	{
		std::cout << "ERROR: NO SE PUDO CARGAR LA TEXTURA " << rutaTextura << '\n';
		exit(-1);
	}

	return textura;
}

ObjetoChico::ObjetoChico(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala)
	: _texture(cargarTextura(rutaTextura)), _sprite(_texture)
{
	_sprite.setPosition(posicion);
	_sprite.setScale({ escala, escala });
	_sprite.setOrigin({ _sprite.getGlobalBounds().size.x / 2, 0 });
	
}

void ObjetoChico::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

sf::FloatRect ObjetoChico::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}
