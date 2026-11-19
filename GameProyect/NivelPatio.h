#pragma once
#include "Nivel.h"

class NivelPatio : public Nivel
{
public:
    NivelPatio();
    ~NivelPatio() override = default;

private:
    void cargarEscenario();
    void cargarEnemigos();
    void cargarMuebles();
    void cargarObjetos();
};

