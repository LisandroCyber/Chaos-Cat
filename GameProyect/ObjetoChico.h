#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ObjetoChico
:	public sf::Drawable
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	
	static sf::Texture cargarTextura(const std::string& rutaTextura);

public:
	
	ObjetoChico(const std::string& rutaTextura, const sf::Vector2f& posicion, float escala);

	sf::FloatRect getGlobalBounds() const;

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;
};
