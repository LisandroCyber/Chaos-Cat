#include "Juego.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    srand((unsigned int)time(NULL));
    Juego juego;
    juego.ejecutar();

    return 0;
}
