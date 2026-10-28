#pragma once
#include "Tutorial.h"
#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include "Personaje.h"
#include "MenuPrincipal.h"
#include "MenuPausa.h"
#include "ConfirmacionSalida.h"
#include "MenuDerrota.h"
#include "Configuracion.h"
#include "MenuConfig.h"
#include "MenuVictoria.h"
#include "MenuSeleccionNivel.h"
#include "Progreso.h"

class Juego
{
public:
    Juego();
    ~Juego();

    void ejecutar();
private:
    sf::RenderWindow _window;

    Personaje _gato;
    Nivel* _nivel;
    sf::View _camara;


    sf::Texture _texturaOjoEscondido;
    sf::Sprite _spriteOjoEscondido;

    MenuPrincipal _menuPrincipal;
    MenuPausa _menuPausa;
    Configuracion _configuracion;
    MenuConfiguracion _menuConfiguracion;
    MenuDerrota _menuDerrota;
    ConfirmacionSalida _menuSalida;
    MenuVictoria _menuVictoria;
    MenuSeleccionNivel _menuSeleccionNivel;
    Progreso _progreso;

    int _nivelActual = 1;
    bool _enSeleccionNivel = false;
    bool _gano = false;
    bool _victoriaMostrada = false;
    bool _enConfiguracion = false;
    bool _perdio = false;
    bool _enMenu = true;
    bool _enPausa = false;
    bool _confirmarSalida = false;
    bool _partidaPausada = true;

    void actualizarCamara();
    void aplicarConfiguracion();
    void procesarEventos();
    void actualizar();
    void actualizarPausaPartida();
    void dibujar();
    void volverAlMenuPrincipal();

    void solicitarSalida();
    void cancelarSalida();
    void reiniciarPartida();

    Nivel* crearNivel(int numero);
    bool iniciarNivel(int numero);
    void abrirSeleccionNivel();

    Tutorial _menuTutorial;
    bool _enTutorial = false;

};
