#pragma once
#include "Nivel.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

class NivelModoInfinito : public Nivel
{
public:
    NivelModoInfinito();
    ~NivelModoInfinito() override;
    void actualizar(Personaje& gato) override;

private:
    static constexpr int CANTIDAD_OBJETOS = 5;

    struct ObjetoActivo
    {
        Objeto* objeto = nullptr;
        std::size_t tipo = 0;
        std::size_t plataforma = 0;
    };

    std::mt19937 _generador{ std::random_device{}() };
    std::array<ObjetoActivo, CANTIDAD_OBJETOS> _objetosActivos{};
    std::vector<Objeto*> _reserva;
    std::uint64_t _objetosGenerados = 0;
    int _enemigosAgregados = 0;

    void cargarEnemigo(int indice);
    void cargarEscenario();
    void cargarMuebles();
    void cargarObjetos();
    void generarObjeto(ObjetoActivo& espacio);
    std::size_t sortearPlataformaLibre();
    int calcularGolpesSiguienteObjeto() const;
};
