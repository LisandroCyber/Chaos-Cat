#include "Juego.h"
#include "Constantes.h"
#include "NivelCocina.h"
#include <iostream>

Juego::Juego()
    : _window(
        sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA),
        "Chaos Cat SFML 2.5"
    ),
    _gato(),
    _nivel(new NivelCocina()),
    _menuConfiguracion(_configuracion)
{
    _window.setFramerateLimit(LIMITE_FPS);
    _window.setKeyRepeatEnabled(false);

    if (_texturaOjoEscondido.loadFromFile("images/ojo_escondido.png"))
    {
        _spriteOjoEscondido.setTexture(_texturaOjoEscondido);

        const sf::Vector2u tamano = _texturaOjoEscondido.getSize();
        const float escala = 96.f / tamano.y;

        _spriteOjoEscondido.setOrigin(tamano.x / 2.f, tamano.y / 2.f);
        _spriteOjoEscondido.setScale(escala, escala);
        _spriteOjoEscondido.setPosition(ANCHO_VENTANA / 2.f, 96.f);
    }
    else
    {
        std::cout << "No se pudo cargar el indicador de escondido\n";
    }

    if (!_configuracion.cargar())
    {
        // Primer inicio o archivo invalido: usa los valores iniciales.
        if (!_configuracion.guardar())
        {
            std::cout << "ERROR AL CARGAR LA CONFIGURACION (cfg.dat)";
        }
    }

    aplicarConfiguracion();

    _nivel->pausarMusica();
    _menuPrincipal.continuarMusica();
}

Juego::~Juego()
{
    delete _nivel;
}

void Juego::ejecutar()
{
    while (_window.isOpen())
    {
        procesarEventos();

        if (!_window.isOpen())
        {
            break;
        }

        actualizar();
        dibujar();
    }
}

void Juego::solicitarSalida()
{
    _confirmarSalida = true;
    _menuSalida.reiniciarSeleccion();

    _menuPrincipal.pausarMusica();
    _menuPausa.pausarMusica();
    _nivel->pausarMusica();
}

void Juego::cancelarSalida()
{
    _confirmarSalida = false;

    if (_enMenu)
    {
        _menuPrincipal.continuarMusica();
    }
    else if (_enPausa)
    {
        _menuPausa.continuarMusica();
    }
    else if (!_perdio && !_gano)
    {
        _nivel->continuarMusica();
    }
}

void Juego::procesarEventos()
{
    sf::Event evento;

    while (_window.pollEvent(evento))
    {
        if (evento.type == sf::Event::Closed)
        {
            solicitarSalida();
            continue;
        }

        // La confirmacion tiene prioridad sobre los otros menus.
        if (_confirmarSalida)
        {
            const int opcion =
                _menuSalida.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _window.close();
                return;
            }
            else if (opcion == 1)
            {
                cancelarSalida();
            }

            continue;
        }

        if (_gano)
        {
            const int opcion =
                _menuVictoria.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                // Continuar: por ahora vuelve al menu. Deberia continuar al siguiente nivel
                volverAlMenuPrincipal();
            }
            else if (opcion == 1)
            {
                volverAlMenuPrincipal();
            }
            else if (opcion == 2)
            {
                solicitarSalida();
            }

            continue;
        }

        if (_enConfiguracion)
        {
            const bool volver =
                _menuConfiguracion.procesarEvento(evento, _window);

            aplicarConfiguracion();

            if (volver)
            {
                _enConfiguracion = false;
            }

            continue;
        }

        if (_perdio)
        {
            const int opcion =
                _menuDerrota.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                reiniciarPartida();
            }
            else if (opcion == 1)
            {
                volverAlMenuPrincipal();
            }
            else if (opcion == 2)
            {
                solicitarSalida();
            }

            continue;
        }

        if (_enMenu)
        {
            const int opcion =
                _menuPrincipal.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _enMenu = false;
                _enConfiguracion = false;

                _menuPrincipal.pausarMusica();
                _nivel->continuarMusica();
            }
            else if (opcion == 1)
            {
                _enConfiguracion = true;
                _menuConfiguracion.abrir();
            }
            else if (opcion == 2)
            {
                solicitarSalida();
            }

            continue;
        }

        if (!_perdio && evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::Escape)
        {
            _enPausa = !_enPausa;

            if (_enPausa)
            {
                _menuPausa.reiniciarSeleccion();

                _nivel->pausarMusica();
                _menuPausa.continuarMusica();
            }
            else
            {
                _menuPausa.pausarMusica();
                _nivel->continuarMusica();
            }

            continue;
        }

        if (_enPausa)
        {
            const int opcion =
                _menuPausa.procesarEvento(evento, _window);

            if (opcion == 0)
            {
                _enPausa = false;

                _menuPausa.pausarMusica();
                _nivel->continuarMusica();
            }
            else if (opcion == 1)
            {
                solicitarSalida();
            }
        }

        if (!_enMenu &&
            !_enConfiguracion &&
            !_enPausa &&
            !_perdio &&
            _configuracion.debugActivado() &&
            evento.type == sf::Event::KeyPressed)
        {
            if (evento.key.code == sf::Keyboard::H)
            {
                _nivel->alternarHitboxes();
            }
            else if (evento.key.code == sf::Keyboard::R)
            {
                _nivel->reiniciarObjetos();
            }
            else if (evento.key.code == sf::Keyboard::M)
            {
                std::cout << "Posicion en x: "
                    << _gato.getPosx() << '\n';

                    std::cout << "Posicion en y: "
                    << _gato.getPosy() << '\n';
            }
        }
    }
}

void Juego::actualizarPausaPartida()
{
    const bool pausada =
        _enMenu || _enConfiguracion || _enPausa ||
        _confirmarSalida || _perdio || _gano;

    if (_partidaPausada == pausada)
    {
        return;
    }

    _gato.setPausado(pausada);
    _nivel->setPausado(pausada);
    _partidaPausada = pausada;
}

void Juego::actualizar()
{
    actualizarPausaPartida();

    if (_partidaPausada)
    {
        return;
    }

    _gato.update();
    _nivel->actualizar(_gato);

    if (_nivel->gatoFueDetectado(_gato))
    {
        _perdio = true;
        actualizarPausaPartida();

        _menuDerrota.reiniciarSeleccion();
        _nivel->pausarMusica();

        return;
    }

    if (!_victoriaMostrada &&
        _nivel->todosLosObjetosEnElPiso())
    {
        _gano = true;
        _victoriaMostrada = true;

        _menuVictoria.reiniciarSeleccion();

        actualizarPausaPartida();
        _nivel->pausarMusica();

        return;
    }

}

void Juego::dibujar()
{
    _window.clear(sf::Color(30, 30, 40));

    if (_enMenu)
    {
        if (_enConfiguracion)
        {
            _window.draw(_menuConfiguracion);
        }
        else
        {
            _window.draw(_menuPrincipal);
        }
    }
    else
    {
        // La partida permanece visible detras de la pausa.
        _nivel->dibujar(_window, _gato);

        if (_gato.estaEscondido())
        {
            _window.draw(_spriteOjoEscondido);
        }

        if (_enPausa)
        {
            _window.draw(_menuPausa);
        }
    }

    if (_perdio)
    {
        _menuDerrota.prepararFondo(_window);
        _window.draw(_menuDerrota);
    }

    if (_gano)
    {
        _menuVictoria.prepararFondo(_window);
        _window.draw(_menuVictoria);
    }

    if (_confirmarSalida)
    {
        _window.draw(_menuSalida);
    }

    _window.display();
}

void Juego::reiniciarPartida()
{
    _menuPrincipal.pausarMusica();
    _menuPausa.pausarMusica();

    // Crear la partida nueva antes de eliminar la anterior.
    Nivel* nuevoNivel = new NivelCocina();

    delete _nivel;
    _nivel = nuevoNivel;

    _gato.reiniciar();
    aplicarConfiguracion();

    _perdio = false;
    _enMenu = false;
    _enPausa = false;
    _confirmarSalida = false;
    _gano = false;
    _victoriaMostrada = false;

    _menuVictoria.reiniciarSeleccion();
    _nivel->continuarMusica();
}

void Juego::aplicarConfiguracion()
{
    sf::Listener::setGlobalVolume(
        static_cast<float>(_configuracion.getVolumenGeneral())
    );

    const float musica =
        static_cast<float>(_configuracion.getVolumenMusica());

    _menuPrincipal.setVolumenMusica(musica);
    _menuPausa.setVolumenMusica(musica);
    _nivel->setVolumenMusica(musica);

    _gato.setUsarFlechas(_configuracion.usaFlechas());

    if (!_configuracion.debugActivado())
    {
        _nivel->ocultarHitboxes();
    }
}

void Juego::volverAlMenuPrincipal()
{
    _nivel->pausarMusica();
    _menuPausa.pausarMusica();

    // Prepara un nivel nuevo para la proxima partida.
    Nivel* nuevoNivel = new NivelCocina();

    delete _nivel;
    _nivel = nuevoNivel;

    _gato.reiniciar();
    aplicarConfiguracion();

    _perdio = false;
    _enMenu = true;
    _enPausa = false;
    _enConfiguracion = false;
    _confirmarSalida = false;
    _gano = false;
    _victoriaMostrada = false;

    _menuVictoria.reiniciarSeleccion();
    // El nivel nuevo y el gato quedan pausados en el menu.
    _nivel->pausarMusica();
    _nivel->setPausado(true);
    _gato.setPausado(true);
    _partidaPausada = true;

    _menuPrincipal.reiniciarSeleccion();
    _menuDerrota.reiniciarSeleccion();

    _menuPrincipal.continuarMusica();
}