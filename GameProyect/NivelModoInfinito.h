#pragma once
#include "Nivel.h"

class NivelModoInfinito : public Nivel
{
public:
    NivelModoInfinito();

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};