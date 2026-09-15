#include "NivelCocina.h"

NivelCocina::NivelCocina()
{
    cargarFondo("images/cocina.png");

    agregarHumano("images/frames_humano.png",
        { 672.f, 664.f },
        600,
        724,
        { 0.7f, 0.82f });

    agregarMueble("images/heladera.png",
        { 3.f, 300.f },
        { 0.25f, 0.272f },
        { { 177.f, 40.f }, { 695.f, 1459.f } });

    agregarMueble("images/mesa-larga.png",
        { 356.06f, 400.f },
        { 0.280825f, 0.384588f },
        { { 47.f, 293.f }, { 1442.f, 561.f } });

    agregarObjeto("images/TazaCafe.png", { 458.f, 490.f }, 0.2f);
    agregarSuperficie({ { 1090.f, 470.f }, { 202.f, 265.f } });
}
