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
	_sprite.setPosition({ 100.f, 100.f });
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

void ObjetoChico::setPeso(float peso) {
	if (peso > 0.5f && peso < 2.f) {
		_peso = peso;
	}
	else {
		std::cout << " Peso Incorrecto (solo entre 0.5 y 2) " << std::endl;
	}
}

void ObjetoChico::setRuido(float ruido) { 
	if (ruido > 0.5f && ruido < 2.f) {
		_ruido = ruido;
	}
	else {
		std::cout << " Ruido Incorrecto (solo entre 0.5 y 2) " << std::endl;
	}
}

void ObjetoChico::setDificultad(float dificultad)
{ 
	if (dificultad > 0.5f && dificultad < 2.f) {
		_dificultad = dificultad;
	}
	else {
		std::cout << " Dificultad Incorrecto (solo entre 0.5 y 2) " << std::endl;
	}
}

float ObjetoChico::getPeso() const {
	return _peso;
}

float ObjetoChico::getRuido() const {
	return _ruido;
}

float ObjetoChico::getDificultad() const {
	return _dificultad;
}

void ObjetoChico::tirarTaza() {

}