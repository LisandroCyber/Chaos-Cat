#include "MenuSeleccionNivel.h"
#include <algorithm>
#include <iostream>
#include <string>

MenuSeleccionNivel::MenuSeleccionNivel()
{
    if (!_texturaFondo.loadFromFile(
        "images/UI/seleccion_niveles/fondo_menu_blur.png"))
    {
        std::cout << "No se pudo cargar el fondo del selector\n";
    }

    if (!_texturaMapa.loadFromFile(
        "images/UI/seleccion_niveles/mapa_casa.png"))
    {
        std::cout << "No se pudo cargar el mapa del selector\n";
    }

    if (!_texturaMarcador.loadFromFile(
        "images/UI/seleccion_niveles/marcador_gato.png"))
    {
        std::cout << "No se pudo cargar el marcador del selector\n";
    }

    if (!_fuente.loadFromFile("fonts/Starcatcher.ttf"))
    {
        std::cout << "No se pudo cargar la fuente del selector\n";
    }

    _fondo.setTexture(_texturaFondo);
    const sf::Vector2u tamanoFondo = _texturaFondo.getSize();
    if (tamanoFondo.x > 0 && tamanoFondo.y > 0)
    {
        _fondo.setScale(
            static_cast<float>(ANCHO_VENTANA) / tamanoFondo.x,
            static_cast<float>(ALTO_VENTANA) / tamanoFondo.y);
    }

    _mapa.setTexture(_texturaMapa);
    //Con esto recorto los margenes transparentes sin perder el tamaño original
    _mapa.setTextureRect(sf::IntRect(40, 110, 1450, 700));
    _mapa.setPosition(60.f, 100.f);
    _mapa.setScale(0.8f, 0.8f);

    _marcador.setTexture(_texturaMarcador);
    const sf::Vector2u tamanoMarcador = _texturaMarcador.getSize();
    if (tamanoMarcador.x > 0 && tamanoMarcador.y > 0)
    {
        const float escala = 70.f / tamanoMarcador.y;
        _marcador.setOrigin(
            tamanoMarcador.x / 2.f, tamanoMarcador.y / 2.f);
        _marcador.setScale(escala, escala);
    }

    _titulo.setFont(_fuente);
    _titulo.setString("SELECCION DE NIVEL");
    _titulo.setCharacterSize(48);
    _titulo.setFillColor(sf::Color(255, 239, 204));
    _titulo.setOutlineColor(sf::Color::Black);
    _titulo.setOutlineThickness(3.f);
    centrarTexto(_titulo, ANCHO_VENTANA / 2.f, 50.f);

    //coordenadas de interfaz en una vista fija de 1280 x 720.
    _zonas[0] = sf::FloatRect(110.f, 375.f, 225.f, 115.f);
    _zonas[1] = sf::FloatRect(390.f, 370.f, 500.f, 115.f);
    _zonas[2] = sf::FloatRect(400.f, 155.f, 490.f, 150.f);
    _zonas[3] = sf::FloatRect(965.f, 375.f, 215.f, 110.f);
    _zonas[4] = sf::FloatRect(110.f, 505.f, 225.f, 110.f);
    _zonas[5] = sf::FloatRect(390.f, 505.f, 500.f, 110.f);

    const std::string nombres[CANTIDAD_NIVELES] = {
        "1. COCINA", "2. LIVING", "3. PATIO", "4. HABITACION", "5. COCINA (NOCHE)", "6. LIVING (NOCHE)"
    };

    for (int i = 0; i < CANTIDAD_NIVELES; i++)
    {
        _nombres[i].setFont(_fuente);
        _nombres[i].setString(nombres[i]);
        _nombres[i].setCharacterSize(24);
        _nombres[i].setOutlineColor(sf::Color::Black);
        _nombres[i].setOutlineThickness(2.f);

        // Deja espacio para la cruz y evita que el nombre salga de su zona.
        while (_nombres[i].getLocalBounds().width > _zonas[i].width - 40.f &&
            _nombres[i].getCharacterSize() > 12)
        {
            _nombres[i].setCharacterSize(
                _nombres[i].getCharacterSize() - 1);
        }

        centrarTexto(_nombres[i],
            _zonas[i].left + _zonas[i].width / 2.f,
            _zonas[i].top + 24.f);
    }

    _volver.setFont(_fuente);
    _volver.setString("Volver");
    _volver.setCharacterSize(24);
    _volver.setOutlineColor(sf::Color::Black);
    _volver.setOutlineThickness(2.f);
    centrarTexto(_volver, 100.f, 690.f);
}

void MenuSeleccionNivel::centrarTexto(sf::Text& texto, float x, float y)
{
    const sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.left + limites.width / 2.f,
        limites.top + limites.height / 2.f);
    texto.setPosition(x, y);
}

void MenuSeleccionNivel::abrir(int ultimoNivelDesbloqueado)
{
    _ultimoNivelDesbloqueado = std::max(1,
        std::min(ultimoNivelDesbloqueado, CANTIDAD_NIVELES));
    _seleccion = 0;
}

bool MenuSeleccionNivel::estaHabilitado(int indice) const
{
    return indice >= 0 && indice < CANTIDAD_NIVELES &&
        _disponibles[indice] && indice + 1 <= _ultimoNivelDesbloqueado;
}

int MenuSeleccionNivel::obtenerNivelEn(
    const sf::Vector2f& posicionMouse) const
{
    for (int i = 0; i < CANTIDAD_NIVELES; i++)
    {
        if (_zonas[i].contains(posicionMouse.x, posicionMouse.y))
        {
            return i;
        }
    }
    return -1;
}

void MenuSeleccionNivel::moverSeleccion(int direccion)
{
    int candidato = _seleccion;
    for (int i = 0; i < CANTIDAD_NIVELES; i++)
    {
        candidato = (candidato + direccion + CANTIDAD_NIVELES) %
            CANTIDAD_NIVELES;
        if (estaHabilitado(candidato))
        {
            _seleccion = candidato;
            return;
        }
    }
}

int MenuSeleccionNivel::procesarEvento(const sf::Event& evento,
    const sf::RenderWindow& ventana)
{
    if (evento.type == sf::Event::MouseMoved)
    {
        const sf::Vector2f mouse = ventana.mapPixelToCoords(
            sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y),
            ventana.getDefaultView());
        const int indice = obtenerNivelEn(mouse);
        if (estaHabilitado(indice))
        {
            _seleccion = indice;
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f mouse = ventana.mapPixelToCoords(
            sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y),
            ventana.getDefaultView());

        if (_volver.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            return 0;
        }

        const int indice = obtenerNivelEn(mouse);
        if (estaHabilitado(indice))
        {
            _seleccion = indice;
            return indice + 1;
        }
    }

    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Escape)
        {
            return 0;
        }
        if (evento.key.code == sf::Keyboard::Right ||
            evento.key.code == sf::Keyboard::Down)
        {
            moverSeleccion(1);
        }
        else if (evento.key.code == sf::Keyboard::Left ||
            evento.key.code == sf::Keyboard::Up)
        {
            moverSeleccion(-1);
        }
        else if (evento.key.code == sf::Keyboard::Enter &&
            estaHabilitado(_seleccion))
        {
            return _seleccion + 1;
        }
    }

    return -1;
}

void MenuSeleccionNivel::draw(sf::RenderTarget& destino,
    sf::RenderStates estados) const
{
    destino.draw(_fondo, estados);
    destino.draw(_mapa, estados);
    destino.draw(_titulo, estados);

    for (int i = 0; i < CANTIDAD_NIVELES; i++)
    {
        const bool habilitado = estaHabilitado(i);
        const bool seleccionado = habilitado && i == _seleccion;
        const sf::FloatRect& zona = _zonas[i];

        if (!habilitado || seleccionado)
        {
            sf::RectangleShape indicador(sf::Vector2f(zona.width, zona.height));
            indicador.setPosition(zona.left, zona.top);
            indicador.setFillColor(habilitado ?
                sf::Color(255, 255, 255, 25) : sf::Color(60, 60, 60, 200));
            if (seleccionado)
            {
                indicador.setOutlineColor(sf::Color(255, 220, 100));
                indicador.setOutlineThickness(2.f);
            }
            destino.draw(indicador, estados);
        }

        sf::Text nombre = _nombres[i];
        nombre.setFillColor(habilitado ?
            sf::Color(255, 239, 204) : sf::Color(180, 180, 180));
        destino.draw(nombre, estados);

        if (!habilitado)
        {
            sf::RectangleShape linea(sf::Vector2f(22.f, 4.f));
            linea.setOrigin(11.f, 2.f);
            linea.setPosition(zona.left + zona.width - 18.f,
                zona.top + zona.height - 18.f);
            linea.setFillColor(sf::Color(230, 90, 90));
            linea.setRotation(45.f);
            destino.draw(linea, estados);
            linea.setRotation(135.f);
            destino.draw(linea, estados);
        }

        if (seleccionado)
        {
            sf::Sprite marcador = _marcador;
            marcador.setPosition(zona.left + zona.width / 2.f,
                zona.top + zona.height * 0.68f);
            destino.draw(marcador, estados);
        }
    }

    destino.draw(_volver, estados);
}
