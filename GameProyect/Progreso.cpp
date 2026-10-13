#include "Progreso.h"
#include "Constantes.h"
#include <cstdio>

bool Progreso::cargar() 
{
	FILE* archivo = fopen("progreso.dat", "rb");

	if (archivo == nullptr)
	{
		return false;
	}

	int ultimo = 1;
	const bool leido = fread(&ultimo, sizeof(int), 1, archivo) == 1;
	fclose(archivo);

	if (!leido || ultimo < 1 || ultimo > CANTIDAD_NIVELES)
	{
		return false;
	}

	_ultimoNivelDesbloqueado = ultimo;
	return true;
}

bool Progreso::guardar() const
{
	FILE* archivo = fopen("progreso.dat", "wb");
	if (archivo == nullptr)
	{
		return false;
	}

	const bool guardado = fwrite(&_ultimoNivelDesbloqueado, sizeof(int), 1, archivo) == 1;
	const bool cerrado = fclose(archivo) == 0;
	return guardado && cerrado;
}

int Progreso::getUltimoNivelDesbloqueado() const
{
	return _ultimoNivelDesbloqueado;
}

void Progreso::desbloquearSiguiente(int nivelCompletado)
{
	if (nivelCompletado < 1 || nivelCompletado >= CANTIDAD_NIVELES)
	{
		return;
	}

	if (nivelCompletado <= _ultimoNivelDesbloqueado &&
		nivelCompletado + 1 > _ultimoNivelDesbloqueado)
	{
		_ultimoNivelDesbloqueado = nivelCompletado + 1;
	}
}
