#include "Enemigo.h"
#include "Constantes.h"
#include "Personaje.h"

#include <cstdlib>
#include <iostream>

sf::Texture Enemigo::cargarTextura(const std::string& rutaTextura)
{
    sf::Texture textura;

    if (!textura.loadFromFile(rutaTextura))
    {
        std::cout << "ERROR: NO SE PUDO CARGAR EL ENEMIGO " << rutaTextura << '\n';
        exit(-1);
    }

    return textura;
}

//sirve para tomar el sprite sheet entero, darle valores a una sola de las imagenes y mantenerlo en el mismo eje que las
// otras. De esta forma da el efecto correcto que el enemigo se da vuelta sobre su propio eje
sf::Vector2f Enemigo::obtenerOrigenVisible(const sf::Texture& textura,
    int frameAncho,
    int frameAlto)
{
    const sf::Image imagen = textura.copyToImage();
    unsigned int izquierda = static_cast<unsigned int>(frameAncho);
    unsigned int derecha = 0;
    unsigned int abajo = 0;
    bool encontroPixelVisible = false;

    //recorre como una matriz el area para detectar la posicion del sprite (sus medidas)
    for (unsigned int y = 0; y < static_cast<unsigned int>(frameAlto); y++)
    {
        for (unsigned int x = 0; x < static_cast<unsigned int>(frameAncho); x++)
        {
            //el a es alpha y es el gradiente de color, si es 0 no hay color por ende es transparente
            if (imagen.getPixel(x, y).a > 0)
            {
                if (x < izquierda)
                {
                    izquierda = x;
                }

                if (x > derecha)
                {
                    derecha = x;
                }

                if (y > abajo)
                {
                    abajo = y;
                }

                encontroPixelVisible = true;
            }
        }
    }

    //si el frame es completamente transparente devuelve un numero fijo asi no explota todo
    if (!encontroPixelVisible)
    {
        return {
            frameAncho / 2.f,
            static_cast<float>(frameAlto)
        };
    }

    return {
        (izquierda + derecha) / 2.f,
        static_cast<float>(abajo)
    };
}

Enemigo::Enemigo(const std::string& rutaTextura,
    const sf::Vector2f& posicion,
    int frameAncho,
    int frameAlto,
    const sf::Vector2f& escala,
    const std::string& rutaSonidoAlerta,
    float volumenAlerta)
    : _textura(cargarTextura(rutaTextura)),
    _sprite(_textura),
    _frameAncho(frameAncho),
    _frameAlto(frameAlto)
{
    validarMedidasFrame();
    mostrarFrame(FRAME_ENEMIGO_REPOSO);
    _sprite.setOrigin(obtenerOrigenVisible(_textura, _frameAncho, _frameAlto));
    _sprite.setPosition(posicion);
    _sprite.setScale(escala);

    if (!rutaSonidoAlerta.empty())
    {
        _tieneSonidoAlerta = _bufferAlerta.loadFromFile(rutaSonidoAlerta);
        if (_tieneSonidoAlerta)
        {
            _sonidoAlerta.setBuffer(_bufferAlerta);
            _sonidoAlerta.setVolume(volumenAlerta);
        }
        else
        {
            std::cout << "ERROR: NO SE PUDO CARGAR EL SONIDO DE ALERTA "
                << rutaSonidoAlerta << '\n';
        }
    }

    cambiarEstado(EstadoEnemigo::DeEspalda);
}

void Enemigo::configurarTiempos(int reposoMinimo, int reposoMaximo,
    float alerta, float vigilancia)
{
    if (reposoMinimo <= 0 || reposoMaximo < reposoMinimo ||
        alerta <= 0.f || vigilancia <= 0.f)
    {
        std::cout << "ERROR: TIEMPOS DE ENEMIGO INVALIDOS\n";
        std::exit(-1);
    }

    _reposoMinimo = reposoMinimo;
    _reposoMaximo = reposoMaximo;
    _duracionAlerta = alerta;
    _duracionVigilancia = vigilancia;

    // Se llama al crear el nivel, antes de iniciar la partida.
    cambiarEstado(EstadoEnemigo::DeEspalda);
}

void Enemigo::configurarRuido(bool reaccionaAlRuido, bool usaReaccionEspecial)
{
    _reaccionaAlRuido = reaccionaAlRuido;
    _usaReaccionEspecial = usaReaccionEspecial;
}

void Enemigo::configurarPresentacion(int frameDeteccion,
    bool usarOrigenVisible)
{
    const int cantidadFrames =
        static_cast<int>(_textura.getSize().x) / _frameAncho;
    if (frameDeteccion != FRAME_ENEMIGO_SIN_CAMBIO &&
        (frameDeteccion < 0 || frameDeteccion >= cantidadFrames))
    {
        std::cout << "ERROR: FRAME DE DETECCION INVALIDO\n";
        std::exit(-1);
    }

    _frameDeteccion = frameDeteccion;
    if (usarOrigenVisible)
    {
        _sprite.setOrigin(obtenerOrigenVisible(_textura, _frameAncho, _frameAlto));
    }
    else
    {
        _sprite.setOrigin(0.f, 0.f);
    }
}

void Enemigo::actualizar()
{
    if (_estado == EstadoEnemigo::Detectado)
    {
        return;
    }

    if (_seAsomaPorPuerta)
    {
        actualizarAsomada();
        return;
    }

    const float tiempoTranscurrido =
        _relojEstado.getElapsedTime().asSeconds();

    if (_estado == EstadoEnemigo::DeEspalda &&
        tiempoTranscurrido >= _tiempoDeEspalda)
    {
        cambiarEstado(EstadoEnemigo::Alerta);
    }
    else if (_estado == EstadoEnemigo::Alerta &&
        tiempoTranscurrido >= _duracionAlerta)
    {
        cambiarEstado(EstadoEnemigo::DadoVuelta);
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado &&
        tiempoTranscurrido >= TIEMPO_ENEMIGO_REACCION_CAIDA)
    {
        cambiarEstado(EstadoEnemigo::DadoVueltaEnojado);
    }
    else if ((_estado == EstadoEnemigo::DadoVuelta ||
        _estado == EstadoEnemigo::DadoVueltaEnojado) &&
        tiempoTranscurrido >= _duracionVigilancia)
    {
        cambiarEstado(EstadoEnemigo::DeEspalda);
    }
}

void Enemigo::reaccionarACaida()
{
    if (_estado == EstadoEnemigo::Detectado || !_reaccionaAlRuido)
    {
        return;
    }

    if (_seAsomaPorPuerta)
    {
        _asomadaEnojada = true;

        if (_estadoAsomada == EstadoEnemigoHabitacion::Fuera ||
            _estadoAsomada == EstadoEnemigoHabitacion::Retirandose)
        {
            cambiarEstadoAsomada(EstadoEnemigoHabitacion::Asomando);
        }
        else
        {
            // Cambia el gesto sin dar tiempo extra si ya estaba mirando.
            actualizarSpriteAsomada();
        }

        return;
    }
    if (!_usaReaccionEspecial)
    {
        // El ruido adelanta la alerta normal sin reiniciar el ciclo en curso.
        if (_estado == EstadoEnemigo::DeEspalda)
        {
            cambiarEstado(EstadoEnemigo::Alerta);
        }
        return;
    }

    // Otra caida no reinicia una reaccion que ya esta en curso.
    if (_estado == EstadoEnemigo::DeEspaldaEnojado ||
        _estado == EstadoEnemigo::DadoVueltaEnojado)
    {
        return;
    }

    if (_estado == EstadoEnemigo::DadoVuelta)
    {
        cambiarEstado(EstadoEnemigo::DadoVueltaEnojado);
    }
    else
    {
        cambiarEstado(EstadoEnemigo::DeEspaldaEnojado);
    }
}

void Enemigo::setPausado(bool pausado)
{
    _relojEstado.setPausado(pausado);

    if (pausado && _sonidoAlerta.getStatus() == sf::SoundSource::Playing)
    {
        _sonidoAlerta.pause();
    }
    else if (!pausado && _sonidoAlerta.getStatus() == sf::SoundSource::Paused)
    {
        _sonidoAlerta.play();
    }
}

void Enemigo::cambiarEstado(EstadoEnemigo nuevoEstado)
{
    _estado = nuevoEstado;

    if (_estado == EstadoEnemigo::DeEspalda)
    {
        const int cantidadDeTiempos = _reposoMaximo -
            _reposoMinimo + 1;
        _tiempoDeEspalda = static_cast<float>(
            _reposoMinimo + std::rand() % cantidadDeTiempos);
    }
    else if (_estado == EstadoEnemigo::Alerta &&
        _tieneSonidoAlerta)
    {
        _sonidoAlerta.play();
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado ||
        _estado == EstadoEnemigo::DadoVueltaEnojado ||
        _estado == EstadoEnemigo::Detectado)
    {
        _sonidoAlerta.stop();
    }

    _relojEstado.restart();
    actualizarSprite();
}

void Enemigo::actualizarSprite()
{
    if (_estado == EstadoEnemigo::Detectado)
    {
        // -1 conserva el cuadro desde el que vio al gato.
        if (_frameDeteccion != FRAME_ENEMIGO_SIN_CAMBIO)
        {
            mostrarFrame(_frameDeteccion);
        }
        return;
    }

    int frame = FRAME_ENEMIGO_REPOSO;
    if (_estado == EstadoEnemigo::Alerta)
    {
        frame = FRAME_ENEMIGO_ALERTA;
    }
    else if (_estado == EstadoEnemigo::DadoVuelta)
    {
        frame = FRAME_ENEMIGO_VIGILANCIA;
    }
    else if (_estado == EstadoEnemigo::DeEspaldaEnojado)
    {
        frame = FRAME_ENEMIGO_REACCION_CAIDA;
    }
    else if (_estado == EstadoEnemigo::DadoVueltaEnojado)
    {
        frame = FRAME_ENEMIGO_VIGILANCIA_ENOJADO;
    }

    mostrarFrame(frame);
}

void Enemigo::dibujar(sf::RenderWindow& ventana) const
{
    if (_seAsomaPorPuerta && _estadoAsomada == EstadoEnemigoHabitacion::Fuera)
    {
        return;
    }

    ventana.draw(_sprite);
}

bool Enemigo::detectaAl(
    const Personaje& gato,
    const sf::FloatRect& areaVisible)
{
    if (_estado == EstadoEnemigo::Detectado)
    {
        return true;
    }

    bool estaMirando = false;
    if (_seAsomaPorPuerta)
    {
        estaMirando = _estadoAsomada == EstadoEnemigoHabitacion::Mirando;
    }
    else
    {
        // Conserva la regla actual de los enemigos fuera de la camara.
        if (!areaVisible.intersects(_sprite.getGlobalBounds()))
        {
            return false;
        }
        estaMirando = _estado == EstadoEnemigo::DadoVuelta ||
            _estado == EstadoEnemigo::DadoVueltaEnojado;
    }

    if (!estaMirando || gato.estaEscondido())
    {
        return false;
    }

    // Actualiza el cuarto frame del perro antes de que Juego abra la derrota.
    cambiarEstado(EstadoEnemigo::Detectado);
    return true;
}

void Enemigo::configurarAsomada()
{
    _seAsomaPorPuerta = true;

    // La mano y la cabeza mantienen la alineacion original de la hoja.
    _sprite.setOrigin(0.f, 0.f);
    _sonidoAlerta.stop();
    cambiarEstadoAsomada(EstadoEnemigoHabitacion::Fuera);
}

void Enemigo::actualizarAsomada()
{
    const float tiempo =
        _relojEstado.getElapsedTime().asSeconds();

    switch (_estadoAsomada)
    {
    case EstadoEnemigoHabitacion::Fuera:
        if (tiempo >= TIEMPO_PUERTA_OCULTO)
        {
            cambiarEstadoAsomada(EstadoEnemigoHabitacion::Asomando);
        }
        break;

    case EstadoEnemigoHabitacion::Asomando:
        if (tiempo >= TIEMPO_PUERTA_ALERTA)
        {
            cambiarEstadoAsomada(EstadoEnemigoHabitacion::Mirando);
        }
        break;

    case EstadoEnemigoHabitacion::Mirando:
        if (tiempo >= TIEMPO_PUERTA_VIGILANCIA)
        {
            cambiarEstadoAsomada(EstadoEnemigoHabitacion::Retirandose);
        }
        break;

    case EstadoEnemigoHabitacion::Retirandose:
        if (tiempo >= TIEMPO_PUERTA_RETIRADA)
        {
            cambiarEstadoAsomada(EstadoEnemigoHabitacion::Fuera);
        }
        break;
    }
}

void Enemigo::cambiarEstadoAsomada(EstadoEnemigoHabitacion nuevoEstado)
{
    _estadoAsomada = nuevoEstado;

    if (_estadoAsomada == EstadoEnemigoHabitacion::Fuera)
    {
        _asomadaEnojada = false;
    }
    else if (_estadoAsomada == EstadoEnemigoHabitacion::Asomando &&
        _tieneSonidoAlerta)
    {
        _sonidoAlerta.play();
    }

    _relojEstado.restart();
    actualizarSpriteAsomada();
}

void Enemigo::actualizarSpriteAsomada()
{
    int frame = FRAME_PUERTA_MANO;

    if (_estadoAsomada == EstadoEnemigoHabitacion::Mirando)
    {
        frame = _asomadaEnojada ? FRAME_PUERTA_ENOJADA : FRAME_PUERTA_MIRANDO;
    }

    mostrarFrame(frame);
}

void Enemigo::validarMedidasFrame() const
{
    const sf::Vector2u tamano = _textura.getSize();
    if (_frameAncho <= 0 || _frameAlto <= 0 ||
        static_cast<unsigned int>(_frameAncho) > tamano.x ||
        static_cast<unsigned int>(_frameAlto) > tamano.y)
    {
        std::cout << "ERROR: MEDIDAS DE FRAME INVALIDAS\n";
        std::exit(-1);
    }
}

void Enemigo::mostrarFrame(int frame)
{
    const int cantidadFrames = static_cast<int>(_textura.getSize().x) / _frameAncho;
    if (frame < 0 || frame >= cantidadFrames)
    {
        std::cout << "ERROR: INDICE DE FRAME FUERA DE LA TEXTURA\n";
        std::exit(-1);
    }

    _sprite.setTextureRect(sf::IntRect(
        frame * _frameAncho, 0, _frameAncho, _frameAlto));
}
