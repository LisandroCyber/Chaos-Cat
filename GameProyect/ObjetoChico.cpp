#include <SFML/Graphics.hpp>
#include "ObjetoChico.h"
#include "Constantes.h"
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
	: _texture(cargarTextura(rutaTextura)), _sprite(_texture), _posicionInicial(posicion),
	  _velocidad({ 0.f, 0.f }), _tirado(false), _visible(true)
{
	_sprite.setPosition(posicion);
	_sprite.setScale({ escala, escala });
	_sprite.setOrigin({ _sprite.getGlobalBounds().size.x / 2, 0 });
	
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

	_sprite.move(_velocidad);
	_velocidad.y += 0.45f;

	if (_sprite.getGlobalBounds().position.y > ALTO_VENTANA)
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

	_tirado = true;
	_velocidad = { 8.f * direccion, -7.f };
}

void ObjetoChico::reiniciar()
{
	_sprite.setPosition(_posicionInicial);
	_velocidad = { 0.f, 0.f };
	_tirado = false;
	_visible = true;
}

bool ObjetoChico::estaTirado() const
{
	return _tirado;
}
