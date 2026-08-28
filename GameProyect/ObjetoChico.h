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

	void setPeso(float peso);
	void setRuido(float ruido);
	void setDificultad(float dificultad);

public:
	
	ObjetoChico();

	void draw(sf::RenderTarget& target,
		sf::RenderStates states) const override;

	float getPeso() const;
	float getRuido() const;
	float getDificultad() const;

	void tirarTaza();
};
