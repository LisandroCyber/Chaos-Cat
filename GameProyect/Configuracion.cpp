#include "Configuracion.h"
#include <cstdio>
#include <algorithm>

bool Configuracion::cargar()
{
    FILE* archivo = fopen("cfg.dat", "rb");

    if (archivo == nullptr)
    {
        return false;
    }

    int datos[4];

    const bool leido =
        fread(datos, sizeof(int), 4, archivo) == 4;

    fclose(archivo);

    if (!leido)
    {
        return false;
    }

    if (datos[0] < 0 || datos[0] > 100 ||
        datos[1] < 0 || datos[1] > 100 ||
        (datos[2] != 0 && datos[2] != 1) ||
        (datos[3] != 0 && datos[3] != 1))
    {
        return false;
    }

    _volumenGeneral = datos[0];
    _volumenMusica = datos[1];
    _usarFlechas = datos[2] == 1;
    _debug = datos[3] == 1;

    return true;
}

bool Configuracion::guardar() const
{
    FILE* archivo = fopen("cfg.dat", "wb");

    if (archivo == nullptr)
    {
        return false;
    }

    int datos[4] = {
        _volumenGeneral,
        _volumenMusica,
        _usarFlechas ? 1 : 0,
        _debug ? 1 : 0
    };

    const bool guardado =
        fwrite(datos, sizeof(int), 4, archivo) == 4;

    const bool cerrado = fclose(archivo) == 0;

    return guardado && cerrado;
}

int Configuracion::getVolumenGeneral() const
{
    return _volumenGeneral;
}

int Configuracion::getVolumenMusica() const
{
    return _volumenMusica;
}

bool Configuracion::usaFlechas() const
{
    return _usarFlechas;
}

bool Configuracion::debugActivado() const
{
    return _debug;
}

void Configuracion::cambiarVolumenGeneral(int cambio)
{
    _volumenGeneral =
        std::max(0, std::min(100, _volumenGeneral + cambio));
}

void Configuracion::cambiarVolumenMusica(int cambio)
{
    _volumenMusica =
        std::max(0, std::min(100, _volumenMusica + cambio));
}

void Configuracion::setUsarFlechas(bool usarFlechas)
{
    _usarFlechas = usarFlechas;
}

void Configuracion::setDebug(bool debug)
{
    _debug = debug;
}