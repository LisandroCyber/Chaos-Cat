#pragma once

class Progreso
{
private:
	int _ultimoNivelDesbloqueado = 1;

public:
	bool cargar();
	bool guardar() const;
	int getUltimoNivelDesbloqueado() const;
	void desbloquearSiguiente(int nivelCompletado);

};

