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
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2.f, 0.f);
	if (!_bufferCaida.loadFromFile("music/vidrioRoto.wav"))
	{
		std::cout << "ERROR: NO SE PUDO CARGAR EL SONIDO DE CAIDA\n";
	}
	else
	{
		_sonidoCaida.setBuffer(_bufferCaida);
		_sonidoCaida.setVolume(60.f);
	}
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
	if (!_tirado || _enElPiso)
	{
		return;
	}

	_sprite.move(_velocidad);
	_velocidad.y += 0.45f;

	const sf::FloatRect limites = _sprite.getGlobalBounds();
	const float ventanaX = static_cast<float>(ANCHO_VENTANA);

	if (limites.left < 0.f)
	{
		_sprite.move(-limites.left, 0.f);
		_velocidad.x = 0.f;
	}
	else if (limites.left + limites.width > ventanaX)
	{
		_sprite.move(ventanaX - (limites.left + limites.width), 0.f);
		_velocidad.x = 0.f;
	}

	const sf::FloatRect area = _sprite.getGlobalBounds();
	const float baseObjeto = area.top + area.height;
	const float pisoY = static_cast<float>(ALTO_VENTANA);

	if (_velocidad.y > 0.f && baseObjeto >= pisoY)
	{
		// Alinear la base del objeto con el borde inferior.
		_sprite.move(0.f, pisoY - baseObjeto);

		_velocidad = sf::Vector2f(0.f, 0.f);
		_enElPiso = true;
		_sonidoCaida.setPlayingOffset(sf::seconds(0.2f));
		_sonidoCaida.play();
	}
}

void Objeto::tirar(float direccion)
{
	if (_tirado)
	{
		return;
	}

	_tirado = true;
	_enElPiso = false;
	_velocidad = sf::Vector2f(8.f * direccion, -7.f);
}

void Objeto::reiniciar()
{
	_sonidoCaida.stop();

	_sprite.setPosition(_posicionInicial);
	_velocidad = sf::Vector2f(0.f, 0.f);

	_tirado = false;
	_visible = true;
	_enElPiso = false;
}

bool Objeto::estaTirado() const
{
	return _tirado;
}
