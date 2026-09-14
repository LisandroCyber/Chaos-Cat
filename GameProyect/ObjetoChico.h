#pragma once
#include <SFML/Graphics.hpp>

class ObjetoChico
:	public sf::Drawable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _velocidad;
	bool _tirado;
	bool _visible;
	
	static sf::Texture cargarTextura();

public:
	
	ObjetoChico();

	void update();
	void tirar(float direccion);
	void reiniciar();
	bool estaTirado() const;
	sf::FloatRect getGlobalBounds() const;

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};
