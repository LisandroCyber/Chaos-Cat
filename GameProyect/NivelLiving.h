#pragma once
#include "Nivel.h"

class NivelLiving : public Nivel
{
public:
    NivelLiving();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};

