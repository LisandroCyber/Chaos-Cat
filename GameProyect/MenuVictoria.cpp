#include "MenuVictoria.h"
#include "Constantes.h"
#include <algorithm>
#include <iostream>

MenuVictoria::MenuVictoria()
    : Menu(3)
{
    if (_texturaGato.loadFromFile("images/Gato/gato_ganador.png"))
    {
        _texturaGato.setSmooth(true);
        _spriteGato.setTexture(_texturaGato);

        const sf::Vector2u tamano = _texturaGato.getSize();
        const float escala = 420.f / tamano.y;

        _spriteGato.setOrigin(tamano.x / 2.f, tamano.y / 2.f);
        _spriteGato.setScale(escala, escala);
        _spriteGato.setPosition(ANCHO_VENTANA / 2.f, 330.f);
    }
    else
    {
        std::cout << "No se pudo cargar la imagen de victoria\n";
    }

    _mensajeInfinito.setFont(_fuente);
    _mensajeInfinito.setString(
        "Ahora proba tus habilidades en el modo infinito");
    _mensajeInfinito.setCharacterSize(28);
    _mensajeInfinito.setFillColor(sf::Color(235, 235, 235));
    centrarTexto(_mensajeInfinito, ANCHO_VENTANA / 2.f, 575.f);

    configurarVictoriaFinal(false);

    //El mismo filtro se aplica primero en horizontal y luego en vertical.
    //Esto esta armado en el lenguaje de los shaders, es mas que nada para aplicar los filtros
    const char* filtroDesenfoque = R"(
        uniform sampler2D textura;
        uniform vec2 direccion;

        void main()
        {
            vec2 uv = gl_TexCoord[0].xy;
            vec4 color = texture2D(textura, uv) * 0.227027;
            color += texture2D(textura, uv + direccion * 1.384615) * 0.316216;
            color += texture2D(textura, uv - direccion * 1.384615) * 0.316216;
            color += texture2D(textura, uv + direccion * 3.230769) * 0.070270;
            color += texture2D(textura, uv - direccion * 3.230769) * 0.070270;
            gl_FragColor = color * gl_Color;
        }
    )";

    if (sf::Shader::isAvailable())
    {
        _shaderDisponible = _shaderDesenfoque.loadFromMemory(
            filtroDesenfoque, sf::Shader::Fragment);

        if (_shaderDisponible)
        {
            _shaderDesenfoque.setUniform("textura", sf::Shader::CurrentTexture);
        }
    }
}

void MenuVictoria::centrarTexto(sf::Text& texto, float x, float y)
{
    const sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.left + limites.width / 2.f,
        limites.top + limites.height / 2.f);
    texto.setPosition(x, y);
}

void MenuVictoria::configurarVictoriaFinal(bool victoriaFinal)
{
    _victoriaFinal = victoriaFinal;
    _cantidadOpciones = victoriaFinal ? 1 : 3;

    _titulo.setString(victoriaFinal ?
        "FELICITACIONES, SOS EL REY DEL CAOS!" : "CAOS TOTAL !");
    _titulo.setCharacterSize(victoriaFinal ? 42 : 55);
    while (_titulo.getLocalBounds().width > ANCHO_VENTANA - 80.f &&
        _titulo.getCharacterSize() > 24)
    {
        _titulo.setCharacterSize(_titulo.getCharacterSize() - 1);
    }
    centrarTexto(_titulo, ANCHO_VENTANA / 2.f, 75.f);

    _opciones[0].setString(victoriaFinal ?
        "Volver a la pantalla de titulo" : "Continuar");
    _opciones[1].setString("Volver al menu principal");
    _opciones[2].setString("Salir");

    for (int i = 0; i < _cantidadOpciones; i++)
    {
        _opciones[i].setCharacterSize(30);
        centrarTexto(_opciones[i], ANCHO_VENTANA / 2.f,
            victoriaFinal ? 650.f : 560.f + i * 60.f);
    }

    reiniciarSeleccion();
}

void MenuVictoria::prepararFondo(const sf::RenderWindow& ventana)
{
    if (_fondoPreparado)
    {
        return;
    }

    const sf::Vector2u tamano = ventana.getSize();
    sf::Texture captura;

    // Sin shaders, reducir y ampliar con suavizado mantiene un desenfoque simple.
    const unsigned int reduccion = _shaderDisponible ? 4u : 12u;
    const sf::Vector2u tamanoReducido(
        std::max(1u, tamano.x / reduccion),
        std::max(1u, tamano.y / reduccion)
    );
    sf::RenderTexture pasoHorizontal;

    if (!captura.create(tamano.x, tamano.y) ||
        !pasoHorizontal.create(tamanoReducido.x, tamanoReducido.y) ||
        !_fondoDesenfocado.create(tamanoReducido.x, tamanoReducido.y))
    {
        std::cout << "No se pudo preparar el fondo de victoria\n";
        return;
    }

    captura.update(ventana);
    captura.setSmooth(true);
    pasoHorizontal.setSmooth(true);
    _fondoDesenfocado.setSmooth(true);

    sf::Sprite spriteCaptura(captura);
    spriteCaptura.setScale(
        static_cast<float>(tamanoReducido.x) / tamano.x,
        static_cast<float>(tamanoReducido.y) / tamano.y
    );

    _fondoDesenfocado.clear();
    _fondoDesenfocado.draw(spriteCaptura);
    _fondoDesenfocado.display();

    if (_shaderDisponible)
    {
        sf::RenderStates estados;
        estados.shader = &_shaderDesenfoque;
        _shaderDesenfoque.setUniform("direccion",
            sf::Glsl::Vec2(1.f / tamanoReducido.x, 0.f));

        pasoHorizontal.clear();
        pasoHorizontal.draw(sf::Sprite(_fondoDesenfocado.getTexture()), estados);
        pasoHorizontal.display();

        _shaderDesenfoque.setUniform("direccion",
            sf::Glsl::Vec2(0.f, 1.f / tamanoReducido.y));

        _fondoDesenfocado.clear();
        _fondoDesenfocado.draw(sf::Sprite(pasoHorizontal.getTexture()), estados);
        _fondoDesenfocado.display();
    }

    _fondoPreparado = true;
}

void MenuVictoria::reiniciarSeleccion()
{
    Menu::reiniciarSeleccion();
    _fondoPreparado = false;
}

void MenuVictoria::draw(
    sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    if (_fondoPreparado)
    {
        sf::Sprite fondoDesenfocado(_fondoDesenfocado.getTexture());
        const sf::Vector2u tamano = _fondoDesenfocado.getSize();
        fondoDesenfocado.setScale(
            ANCHO_VENTANA / static_cast<float>(tamano.x),
            ALTO_VENTANA / static_cast<float>(tamano.y)
        );
        destino.draw(fondoDesenfocado, estados);
    }

    sf::RectangleShape fondo(sf::Vector2f(
        static_cast<float>(ANCHO_VENTANA),
        static_cast<float>(ALTO_VENTANA)
    ));

    fondo.setFillColor(sf::Color(0, 0, 0, 150));

    destino.draw(fondo, estados);
    destino.draw(_spriteGato, estados);
    if (_victoriaFinal)
    {
        destino.draw(_mensajeInfinito, estados);
    }
    Menu::draw(destino, estados);
}
