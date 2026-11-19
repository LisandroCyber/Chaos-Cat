#pragma once

#include "Nivel.h"

class NivelHabitacion : public Nivel
{
public:
    NivelHabitacion();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};

