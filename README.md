# Chaos Cat 🐈

**Chaos Cat** es un videojuego arcade 2D en desarrollo, creado en **C++** con **SFML 3**.

El jugador controla a un gato cuyo objetivo es tirar objetos sin ser descubierto por el dueño de la casa.

## Rama de desarrollo

La versión más reciente del prototipo se encuentra en la rama `EnProceso`.

> El prototipo actual utiliza una **vista lateral**. La perspectiva definitiva del juego todavía está en evaluación.

## 🎮 Idea del juego

Cada nivel representará una habitación diferente de la casa. El gato deberá tirar una cantidad determinada de objetos antes de que termine el tiempo.

El dueño estará en la misma habitación realizando otras actividades, pero podrá darse vuelta inesperadamente. Una animación, un sonido o ambos podrán advertir al jugador antes de que mire.

Cuando un objeto caiga hará ruido y el dueño se dará vuelta. Mientras esté mirando, el gato deberá permanecer quieto; si se mueve, será descubierto y perderá. Después de aproximadamente **3 segundos**, el dueño retomará su actividad.

También se evalúa una variante avanzada: después de tirar un objeto, el gato tendrá **3 segundos para esconderse** antes de ser atrapado.

## Estado actual

El prototipo de `EnProceso` incluye:

- Movimiento horizontal del gato.
- Distintas velocidades para caminar, correr y avanzar agachado.
- Salto y gravedad.
- Animaciones de quieto, caminando, agachado, saltando y sentado.
- Límites de movimiento dentro de una ventana de 1280 × 720.
- Hitboxes adaptadas al estado y la animación del gato.
- Colisiones entre el gato y una taza.
- Posibilidad de saltar sobre la taza, apoyarse en ella y chocar con su parte inferior.
- Fondo y sprites cargados desde archivos externos.
- Visualización de las hitboxes del gato y de la taza para depuración.

### Últimos cambios: lanzamiento de la taza

La taza ya se puede tirar cuando el gato la toca, se encuentra a uno de sus costados o está apoyado sobre ella.

Al presionar `Espacio`:

1. La taza recibe un impulso horizontal hacia el lado opuesto al gato.
2. También recibe un impulso vertical inicial.
3. Su velocidad vertical aumenta en cada actualización, simulando gravedad.
4. Al salir por debajo de la pantalla deja de dibujarse.
5. Una vez lanzada deja de funcionar como superficie de colisión; si el gato estaba apoyado encima, comienza a caer.

Durante las pruebas, la taza puede volver a su posición inicial con `R`.

## Controles actuales

| Tecla | Acción |
|---|---|
| `A` | Moverse hacia la izquierda |
| `D` | Moverse hacia la derecha |
| `W` | Saltar |
| `Shift izquierdo` | Correr |
| `Ctrl izquierdo` | Agacharse y moverse lentamente |
| `Espacio` | Tirar la taza cuando está al alcance |
| `R` | Reiniciar la taza (depuración) |
| `M` | Mostrar la posición del gato en la consola (depuración) |

## Tecnologías

- **C++17**
- **SFML 3**
- **Visual Studio**
- Programación orientada a objetos

## Estructura principal

```text
Chaos-Cat/
├── GameProyect.slnx
├── GameProyect/
│   ├── Juego.cpp / Juego.h
│   ├── Personaje.cpp / Personaje.h
│   ├── ObjetoChico.cpp / ObjetoChico.h
│   ├── main.cpp
│   ├── images/
│   └── SFML/
└── README.md
```

### Clases principales

- **`Juego`**: administra la ventana, el ciclo principal, los eventos, las actualizaciones, el dibujo, las colisiones y la interacción para tirar la taza.
- **`Personaje`**: representa al gato y controla su movimiento, estados, animaciones, salto, gravedad e hitbox.
- **`ObjetoChico`**: representa objetos pequeños interactivos. Actualmente controla la taza, su impulso, gravedad, visibilidad y reinicio.

## Próximos pasos

- Agregar una animación de caída y rotura para la taza.
- Incorporar el sonido del objeto al caer y romperse.
- Generalizar la mecánica para distintos tipos de objetos.
- Incorporar al dueño y sus estados de actividad, aviso, vigilancia y regreso a su tarea.
- Detectar si el gato se mueve mientras está siendo observado.
- Implementar escondites y definir la variante de 3 segundos.
- Crear habitaciones, niveles, objetivos y un temporizador.
- Agregar condiciones de victoria y derrota.
- Mejorar y reorganizar el sistema de hitboxes.
- Añadir pantallas de inicio, victoria y derrota, además de un sistema de puntaje.

## Decisiones abiertas

- **Perspectiva definitiva:** mantener la vista lateral del prototipo o volver a una vista desde arriba.
- **Aviso de vigilancia:** usar una animación, un sonido o ambos antes de que el dueño se dé vuelta.
- **Reacción después del ruido:** quedarse quieto, esconderse en 3 segundos o utilizar ambas mecánicas según el nivel o la dificultad.
