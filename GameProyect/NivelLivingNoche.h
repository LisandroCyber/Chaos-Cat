#pragma once

#include "Nivel.h"

class NivelLivingNoche : public Nivel
{
public:
    NivelLivingNoche();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};

