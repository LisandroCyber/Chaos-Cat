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
	_velocidad = { 0.f, 0.f };
	_tirado = false;
	_visible = true;
}

void ObjetoChico::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_visible)
	{
		target.draw(_sprite, states);
	}
}

sf::FloatRect ObjetoChico::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}

void ObjetoChico::update()
{
	if (!_tirado)
	{
		return;
	}

	// La taza conserva su impulso y la gravedad aumenta la velocidad hacia abajo.
	_sprite.move(_velocidad);
	_velocidad.y += 0.45f;

	// Deja de dibujarse cuando termina de caer fuera de la pantalla.
	if (_sprite.getGlobalBounds().position.y > 720.f)
	{
		_visible = false;
	}
}

void ObjetoChico::tirar(float direccion)
{
	if (_tirado)
	{
		return;
	}

	// direccion vale -1 para la izquierda y 1 para la derecha.
	_tirado = true;
	_velocidad = { 8.f * direccion, -7.f };
}

void ObjetoChico::reiniciar()
{
	_sprite.setPosition({ 458.f, 478.f });
	_velocidad = { 0.f, 0.f };
	_tirado = false;
	_visible = true;
}

bool ObjetoChico::estaTirado() const
{
	return _tirado;
}
