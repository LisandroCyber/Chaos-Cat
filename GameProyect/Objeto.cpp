#include <SFML/Graphics.hpp>
#include "Objeto.h"
#include "Constantes.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

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

Objeto::Objeto(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala,
	int golpesNecesarios, const std::string& rutaTexturaCaida, const std::string& rutaSonidoCaida)
	: _texture(cargarTextura(rutaTextura)),
	_texturaCaida(cargarTextura(rutaTexturaCaida)),
	_sprite(_texture),
	_posicionInicial(posicion),
	_velocidad({ 0.f, 0.f }),
	_tirado(false),
	_visible(true),
	_golpesNecesarios(golpesNecesarios > 0 ? golpesNecesarios : 1)
{
	_sprite.setPosition(posicion);
	_sprite.setScale({ escala, escala });
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2.f, 0.f);
	crearContorno();

	if (!_bufferCaida.loadFromFile(rutaSonidoCaida))
	{
		std::cout << "ERROR: NO SE PUDO CARGAR EL SONIDO DE CAIDA: " << rutaSonidoCaida << "\n";
	}
	else
	{
		_sonidoCaida.setBuffer(_bufferCaida);
		_sonidoCaida.setVolume(45.f);
	}
}

void Objeto::crearContorno()
{
	const float escala = std::abs(_sprite.getScale().x);
	if (escala == 0.f)
	{
		return;
	}

	const sf::Image imagen = _texture.copyToImage();
	const sf::Vector2u tamano = imagen.getSize();
	// El margen permite que el halo se desvanezca fuera de la silueta.
	const int ancho = static_cast<int>(std::ceil(tamano.x * escala)) + RADIO_CONTORNO * 2;
	const int alto = static_cast<int>(std::ceil(tamano.y * escala)) + RADIO_CONTORNO * 2;
	std::vector<sf::Uint8> mascara(ancho * alto, 0);

	//uso radio contorno para crear un "halo" y no una linea,asi queda mas bonito
	for (int y = RADIO_CONTORNO; y < alto - RADIO_CONTORNO; y++)
	{
		for (int x = RADIO_CONTORNO; x < ancho - RADIO_CONTORNO; x++)
		{
			const unsigned int origenX = std::min(tamano.x - 1,
				static_cast<unsigned int>((x - RADIO_CONTORNO + 0.5f) / escala));
			const unsigned int origenY = std::min(tamano.y - 1,
				static_cast<unsigned int>((y - RADIO_CONTORNO + 0.5f) / escala));
			mascara[y * ancho + x] = imagen.getPixel(origenX, origenY).a >= 128;
		}
	}

	sf::Image contorno;
	contorno.create(ancho, alto, sf::Color::Transparent);
	const float opacidadMaxima = 265.f;
	const float suavidad = 1.6f;

	for (int y = 0; y < alto; y++)
	{
		for (int x = 0; x < ancho; x++)
		{
			if (mascara[y * ancho + x])
			{
				continue;
			}

			int distanciaCuadrada = RADIO_CONTORNO * RADIO_CONTORNO + 1;
			for (int dy = -RADIO_CONTORNO; dy <= RADIO_CONTORNO; dy++)
			{
				for (int dx = -RADIO_CONTORNO; dx <= RADIO_CONTORNO; dx++)
				{
					const int vecinoX = x + dx;
					const int vecinoY = y + dy;
					if (vecinoX >= 0 && vecinoX < ancho &&
						vecinoY >= 0 && vecinoY < alto &&
						mascara[vecinoY * ancho + vecinoX])
					{
						distanciaCuadrada = std::min(distanciaCuadrada, dx * dx + dy * dy);
					}
				}
			}

			if (distanciaCuadrada <= RADIO_CONTORNO * RADIO_CONTORNO)
			{
				const float intensidad = std::exp(-distanciaCuadrada / (2.f * suavidad * suavidad));
				const sf::Uint8 opacidad = static_cast<sf::Uint8>(opacidadMaxima * intensidad);
				contorno.setPixel(x, y, sf::Color(240, 80, 65, opacidad));
			}
		}
	}

	if (!_texturaContorno.loadFromImage(contorno))
	{
		std::cout << "ERROR: NO SE PUDO CREAR EL CONTORNO DEL OBJETO\n";
	}
	else
	{
		_texturaContorno.setSmooth(true);
	}
}

void Objeto::dibujar(sf::RenderWindow& ventana) const
{
	if (_visible)
	{
		if (!_tirado && _texturaContorno.getSize().x > 0)
		{
			sf::Sprite contorno(_texturaContorno);
			contorno.setOrigin(
				_sprite.getOrigin().x * _sprite.getScale().x + RADIO_CONTORNO,
				_sprite.getOrigin().y * _sprite.getScale().y + RADIO_CONTORNO);
			contorno.setPosition(_sprite.getPosition());
			ventana.draw(contorno);
		}

		ventana.draw(_sprite);
	}
}

sf::FloatRect Objeto::getGlobalBounds() const
{
	return _sprite.getGlobalBounds();
}

void Objeto::update(float anchoNivel)
{
	if (!_tirado || _enElPiso)
	{
		return;
	}

	_sprite.move(_velocidad);
	_velocidad.y += 0.45f;

	const sf::FloatRect limites = _sprite.getGlobalBounds();
	const float ventanaX = anchoNivel;

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
		_sprite.setTexture(_texturaCaida, true);
		_sprite.move(0.f, pisoY - baseObjeto);

		_velocidad = sf::Vector2f(0.f, 0.f);
		_enElPiso = true;
		_sonidoCaida.setPlayingOffset(sf::seconds(0.2f));
		_sonidoCaida.play();
	}
}

void Objeto::setPausado(bool pausado)
{
	if (pausado && _sonidoCaida.getStatus() == sf::SoundSource::Playing)
	{
		_sonidoCaida.pause();
	}
	else if (!pausado && _sonidoCaida.getStatus() == sf::SoundSource::Paused)
	{
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

	_sprite.setTexture(_texture, true);
	_sprite.setPosition(_posicionInicial);
	_velocidad = sf::Vector2f(0.f, 0.f);

	_tirado = false;
	_visible = true;
	_enElPiso = false;
	_golpesRecibidos = 0;
	_ultimoGolpeRecibido = -1;
}

bool Objeto::estaTirado() const
{
	return _tirado;
}

bool Objeto::estaEnElPiso() const
{
	return _enElPiso;
}

void Objeto::recibirGolpe(float direccion, int numeroGolpe)
{
	if (_tirado || _ultimoGolpeRecibido == numeroGolpe)
	{
		return;
	}

	_ultimoGolpeRecibido = numeroGolpe;
	_golpesRecibidos++;

	if (_golpesRecibidos >= _golpesNecesarios)
	{
		tirar(direccion);
	}
}

