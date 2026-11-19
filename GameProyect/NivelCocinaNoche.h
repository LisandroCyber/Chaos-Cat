#pragma once

#include "Nivel.h"

class NivelCocinaNoche : public Nivel
{
public:
    NivelCocinaNoche();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};

