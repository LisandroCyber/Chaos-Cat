#include "Juego.h"
#include <cstdlib>
int main()
{
    std::srand(std::time(NULL));
    Juego juego;
    juego.ejecutar();

    return 0;
}
