#pragma once
#include <SFML/Graphics.hpp>

class ObjetoChico
:	public sf::Drawable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	static sf::Texture cargarTextura();

public:
	
	ObjetoChico();

	sf::FloatRect getGlobalBounds() const;

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};
