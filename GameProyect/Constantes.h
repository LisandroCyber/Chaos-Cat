#pragma once

//Ventana.
const unsigned int ANCHO_VENTANA = 1280;
const unsigned int ALTO_VENTANA = 720;
const unsigned int LIMITE_FPS = 144;

//Medidas originales del hitbox base, antes de aplicar la escala.
const float ANCHO_BASE_HITBOX = 360.f;
const float ALTO_BASE_HITBOX = 360.f;

//Movimiento y gravedad: valores por actualizacion.
const float VELOCIDAD_CAMINAR = 2.2f;
const float VELOCIDAD_CORRER = 5.f;
const float VELOCIDAD_AGACHADO = 0.75f;
const float GRAVEDAD = 0.55f;
const float VELOCIDAD_INICIAL_SALTO = -17.f;

//Tiempos en segundos.
const float TIEMPO_PARA_SENTARSE = 0.5f;
const float DURACION_FRAME_CAMINAR = 0.18f;
const float DURACION_FRAME_AGACHADO = 0.22f;
const float DURACION_FRAME_GOLPE = 0.10f;
const float DURACION_GOLPE = 0.20f;

//Ciclo de vigilancia del enemigo.
const int TIEMPO_ENEMIGO_DE_ESPALDA_MIN = 3;
const int TIEMPO_ENEMIGO_DE_ESPALDA_MAX = 8;
const float TIEMPO_ENEMIGO_ALERTA = 2.f;
const float TIEMPO_ENEMIGO_REACCION_CAIDA = 1.3f;
const float TIEMPO_ENEMIGO_DADO_VUELTA = 3.f;

//Enemigo que se asoma por la puerta.
const float TIEMPO_PUERTA_OCULTO = 8.f;
const float TIEMPO_PUERTA_ALERTA = 2.f;
const float TIEMPO_PUERTA_VIGILANCIA = 3.f;
const float TIEMPO_PUERTA_RETIRADA = 1.f;

//Seleccion de niveles
const int CANTIDAD_NIVELES = 6;

//Ciclo del perro: tiempos en segundos.
const int TIEMPO_PERRO_REPOSO = 8;
const float TIEMPO_PERRO_ALERTA = 2.f;
const float TIEMPO_PERRO_VIGILANCIA = 3.f;

//Ciclo de la camara: tiempos en segundos.
const int TIEMPO_CAMARA_REPOSO = 5;
const float TIEMPO_CAMARA_ALERTA = 5.f;
const float TIEMPO_CAMARA_VIGILANCIA = 5.f;

//Indices del spritesheet: se cuentan desde cero.
const int FRAME_ENEMIGO_REPOSO = 0;
const int FRAME_ENEMIGO_ALERTA = 1;
const int FRAME_ENEMIGO_VIGILANCIA = 2;
const int FRAME_ENEMIGO_REACCION_CAIDA = 3;
const int FRAME_ENEMIGO_VIGILANCIA_ENOJADO = 4;
const int FRAME_ENEMIGO_SIN_CAMBIO = -1;
const int FRAME_PERRO_DETECCION = 3;

//Cuadros propios de la duenia de Habitacion.
const int FRAME_PUERTA_MANO = 0;
const int FRAME_PUERTA_MIRANDO = 1;
const int FRAME_PUERTA_ENOJADA = 2;

//Volumenes independientes: valores iniciales que podes ajustar por enemigo.
const float VOLUMEN_ALERTA_DUENIO = 5.f;
const float VOLUMEN_ALERTA_DUENIA_LIVING = 5.f;
const float VOLUMEN_ALERTA_DUENIA_HABITACION = 5.f;
const float VOLUMEN_ALERTA_PERRO = 5.f;
const float VOLUMEN_ALERTA_CAMARA = 5.f;