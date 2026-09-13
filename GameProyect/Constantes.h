#pragma once

// Ventana.
const unsigned int ANCHO_VENTANA = 1280;
const unsigned int ALTO_VENTANA = 720;
const unsigned int LIMITE_FPS = 144;

// Medidas originales del hitbox base, antes de aplicar la escala.
const float ANCHO_BASE_HITBOX = 360.f;
const float ALTO_BASE_HITBOX = 360.f;

// Movimiento y gravedad: valores por actualizacion.
const float VELOCIDAD_CAMINAR = 2.2f;
const float VELOCIDAD_CORRER = 5.f;
const float VELOCIDAD_AGACHADO = 0.75f;
const float GRAVEDAD = 0.55f;
const float VELOCIDAD_INICIAL_SALTO = -17.f;

// Tiempos en segundos.
const float TIEMPO_PARA_SENTARSE = 0.5f;
const float DURACION_FRAME_CAMINAR = 0.18f;
const float DURACION_FRAME_AGACHADO = 0.22f;
