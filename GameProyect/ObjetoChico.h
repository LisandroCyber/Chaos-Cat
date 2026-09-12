#pragma once
#include <SFML/Graphics.hpp>

class ObjetoChico
:	public sf::Drawable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	float _peso;
	float _ruido;
	float _dificultad;

	static sf::Texture cargarTextura();

public:
	
	ObjetoChico();

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};
