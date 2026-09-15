#include <SFML/Graphics.hpp>
#include "Objeto.h"
#include "Constantes.h"
#include <cstdlib>
#include <iostream>

sf::Texture Objeto::cargarTextura(const std::string& rutaTextura)
{
	sf::Texture textura;

	if (!textura.loadFromFile(rutaTextura))
	{
		std::cout << "ERROR: NO SE PUDO CARGAR LA TEXTURA " << rutaTextura << '\n';
		exit(-1);
	}

	return textura;
}

Objeto::Objeto(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala)
	: _texture(cargarTextura(rutaTextura)), _sprite(_texture), _posicionInicial(posicion),
	  _velocidad({ 0.f, 0.f }), _tirado(false), _visible(true)
{
	_sprite.setPosition(posicion);
	_sprite.setScale({ escala, escala });
	_sprite.setOrigin({ _sprite.getGlobalBounds().size.x / 2, 0 });
	
}

void Objeto::dibujar(sf::RenderWindow& ventana) const
{
	if (_visible)
	{
		ventana.draw(_sprite);
	}
}

sf::FloatRect Objeto::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}

void Objeto::update()
{
	if (!_tirado)
	{
		return;
	}

	_sprite.move(_velocidad);
	_velocidad.y += 0.45f;

	if (_sprite.getGlobalBounds().position.y > ALTO_VENTANA)
	{
		_visible = false;
	}
}

void Objeto::tirar(float direccion)
{
	if (_tirado)
	{
		return;
	}

	_tirado = true;
	_velocidad = { 8.f * direccion, -7.f };
}

void Objeto::reiniciar()
{
	_sprite.setPosition(_posicionInicial);
	_velocidad = { 0.f, 0.f };
	_tirado = false;
	_visible = true;
}

bool Objeto::estaTirado() const
{
	return _tirado;
}
