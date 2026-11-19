#pragma once

class Configuracion
{
private:
    int _volumenGeneral = 100;
    int _volumenMusica = 25;
    bool _usarFlechas = false;
    bool _debug = false;

public:
    bool cargar();
    bool guardar() const;

    int getVolumenGeneral() const;
    int getVolumenMusica() const;
    bool usaFlechas() const;
    bool debugActivado() const;

    void cambiarVolumenGeneral(int cambio);
    void cambiarVolumenMusica(int cambio);
    void setUsarFlechas(bool usarFlechas);
    void setDebug(bool debug);
};