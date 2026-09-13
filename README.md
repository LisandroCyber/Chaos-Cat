# Chaos Cat 🐈

**Chaos Cat** es un videojuego arcade en 2D desarrollado en **C++** con **SFML 3**.

El jugador controla a un gato travieso dentro de una casa. Su objetivo será recorrer las habitaciones y tirar distintos objetos antes de que el dueño lo descubra.

> El proyecto se encuentra actualmente en desarrollo.

## Estado actual

En la versión disponible en la rama `EnProceso` ya se encuentran implementadas las siguientes funciones:

- Movimiento del gato en cuatro direcciones.
- Diferentes velocidades: caminar, correr y agacharse.
- Salto y gravedad.
- Animaciones según el estado del gato.
- Límites de movimiento dentro de la ventana.
- Hitboxes adaptadas a las distintas animaciones.
- Colisión entre el gato y una taza.
- Posibilidad de saltar y apoyarse sobre objetos.
- Fondo y sprites cargados desde archivos externos.

Actualmente, al tocar la taza se muestra el mensaje `TIRAR TAZA` en la consola. El movimiento físico y la caída del objeto todavía no están implementados.

## Controles

| Tecla | Acción |
|---|---|
| `W` | Moverse hacia arriba |
| `A` | Moverse hacia la izquierda |
| `S` | Moverse hacia abajo |
| `D` | Moverse hacia la derecha |
| `Shift izquierdo` | Correr |
| `Ctrl izquierdo` | Agacharse |
| `Espacio` | Saltar |
| `M` | Mostrar la posición del gato en la consola |

## Mecánica planeada

Cada nivel representará una habitación diferente de la casa y tendrá una cantidad determinada de objetos que deberán tirarse dentro de un tiempo límite.

El dueño estará en la misma habitación realizando otras tareas y podrá darse vuelta de forma inesperada. Una animación o un sonido podrán advertir al jugador antes de que esto ocurra.

Cuando el dueño esté mirando, el gato deberá permanecer quieto. Si el jugador se mueve, será descubierto y perderá la partida.

Al tirar un objeto, el ruido hará que el dueño se dé vuelta. Como mecánica avanzada, el gato tendrá unos segundos para esconderse antes de ser atrapado.

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

- **`Juego`**: administra la ventana, el ciclo principal, los eventos, las actualizaciones, el dibujo y las colisiones.
- **`Personaje`**: representa al gato y controla su movimiento, estados, animaciones, salto, gravedad e hitbox.
- **`ObjetoChico`**: representa objetos pequeños con los que puede interactuar el gato, actualmente una taza.

## Cómo ejecutar el proyecto

### Requisitos

- Windows 10 o posterior.
- Visual Studio con la carga de trabajo **Desarrollo para el escritorio con C++**.
- Plataforma de compilación **x64**.

La versión de SFML utilizada por el proyecto ya se encuentra incluida en la carpeta `GameProyect/SFML`.

### Pasos

1. Clonar la rama de desarrollo:

```bash
git clone --branch EnProceso https://github.com/LisandroCyber/Chaos-Cat.git
```

2. Abrir el archivo `GameProyect.slnx` con Visual Studio.
3. Seleccionar la plataforma **x64**.
4. Elegir la configuración **Debug** o **Release**.
5. Compilar y ejecutar el proyecto.

> El ejecutable debe iniciarse con la carpeta `GameProyect` como directorio de trabajo para que pueda encontrar los recursos de `images/`.

## Próximos pasos

- Implementar el empuje y la caída de los objetos.
- Agregar sonidos al tirar objetos.
- Incorporar al dueño y sus estados de comportamiento.
- Detectar si el gato se mueve mientras el dueño está mirando.
- Añadir escondites y el tiempo límite para ocultarse.
- Crear habitaciones y niveles.
- Agregar objetivos, temporizador y condiciones de victoria o derrota.
- Mejorar y reorganizar el sistema de hitboxes.

## Rama de desarrollo

El trabajo actual se realiza en la rama [`EnProceso`](https://github.com/LisandroCyber/Chaos-Cat/tree/EnProceso).
