#pragma once

#include "Nivel.h"

class NivelCocina : public Nivel
{
public:
    NivelCocina();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};
