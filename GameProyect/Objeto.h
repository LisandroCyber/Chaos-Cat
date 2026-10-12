#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Objeto
{
private:
	sf::Texture _texture;
	sf::Texture _texturaCaida;
	sf::Sprite _sprite;
	sf::Vector2f _posicionInicial;
	sf::Vector2f _velocidad;
	bool _tirado;
	bool _visible;
	bool _enElPiso = false;
	int _golpesNecesarios;
	int _golpesRecibidos = 0;
	int _ultimoGolpeRecibido = -1;

	sf::SoundBuffer _bufferCaida;
	sf::Sound _sonidoCaida;
	
	static sf::Texture cargarTextura(const std::string& rutaTextura);

public:
	
	Objeto(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala,
		int golpesNecesarios, const std::string& rutaTexturaCaida, const std::string& rutaSonidoCaida);

	sf::FloatRect getGlobalBounds() const;
	void update(float anchoNivel);
	void setPausado(bool pausado);
	void tirar(float direccion);
	void reiniciar();
	bool estaTirado() const;
	bool estaEnElPiso() const;
	void recibirGolpe(float direccion, int numeroGolpe);

	void dibujar(sf::RenderWindow& ventana) const;
};
