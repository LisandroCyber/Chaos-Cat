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
# 🐱 Chaos Cat

**Chaos Cat** es un juego arcade 2D en desarrollo, creado en C++ con SFML 3. Controlás a un gato que quiere tirar objetos de las mesas de distintas habitaciones de una casa sin que su dueño lo atrape.

Cada habitación será un nivel: habrá una cantidad de objetos por tirar y un tiempo límite. El dueño estará en la misma habitación, ocupado con sus cosas, pero podrá darse vuelta para vigilar al gato. Hacer caer un objeto provocará ruido y llamará su atención.

> **Estado:** prototipo jugable de movimiento y renderizado. Las reglas de sigilo, los niveles y el sistema de puntuación que se describen a continuación son el diseño previsto; todavía no están implementados.

## 🎮 Cómo se jugará

1. El gato se moverá sobre la mesa de la habitación y empujará los objetos para hacerlos caer.
2. El dueño hará otras actividades, pero podrá darse vuelta en cualquier momento. Se evalúa avisar al jugador con una animación o un sonido antes de que mire.
3. Cuando un objeto caiga, hará ruido y el dueño se dará vuelta necesariamente.
4. Mientras el dueño esté mirando, el gato deberá permanecer quieto: si se mueve, será descubierto y perderá. Después de aproximadamente **3 segundos**, el dueño volverá a su actividad.
5. Para completar un nivel, habrá que tirar los objetos requeridos antes de que se agote el tiempo, sin ser descubierto.

La idea es combinar el caos de tirar cosas con una mecánica de «quedarse inmóvil» en el momento justo.

### Variante avanzada por definir

Se considera una alternativa para el momento posterior a tirar un objeto: darle al gato **3 segundos para esconderse** antes de que el dueño lo atrape. Esto requeriría una regla de detección distinta de la regla básica de quedarse quieto y **todavía no se decidió** si reemplazará esa regla o si será un modo/dificultad aparte.

## ✅ Qué funciona hoy

- Ventana de 1280 × 720 con fondo, gato y una taza en pantalla.
- Movimiento del gato en cuatro direcciones con WASD, con opciones de correr y agacharse.
- Cambio de orientación horizontal del sprite y límites de movimiento dentro de la ventana.
- Carga de imágenes y clases separadas para el personaje y el objeto.
- Límite configurado de 144 FPS.

La taza se dibuja en pantalla, pero **todavía no se puede empujar ni tirar**. Tampoco hay dueño, niveles, temporizador, detección, sonido ni puntaje funcionales.

### Controles actuales

| Tecla | Acción |
| --- | --- |
| W / A / S / D | Mover al gato |
| Shift izquierdo | Correr |
| Ctrl izquierdo | Agacharse |
| M | Mostrar la posición del gato en la consola |

## 🧭 Dirección del proyecto

### Próximas mecánicas

- Colisiones e interacción para empujar objetos y hacerlos caer.
- Sonido de caída y reacción del dueño ante el ruido.
- Dueño con estados de actividad, aviso, vigilancia y retorno a su actividad.
- Detección del movimiento del gato mientras es observado y condición de derrota.
- Habitaciones como niveles, cada una con objetivos de objetos y tiempo límite.
- Puntaje y pantallas de inicio, victoria y derrota.

### Ideas para más adelante

- Posiciones aleatorias de los objetos en cada partida.
- Dificultades con más personas atentas al gato y patrones de movimiento distintos.
- Modo infinito con aparición continua de objetos y contador de objetos tirados.
- Recompensas por hitos, por ejemplo, tirar 50 objetos o alcanzar cierta puntuación.
- Evaluar si el gato puede seguir tirando cosas mientras escapa del dueño.
- Configuración de pantalla completa o ventana, volumen y elección entre WASD y flechas.

### Decisiones abiertas

- **Perspectiva visual:** vista desde arriba o de frente. El prototipo actual usa movimiento en cuatro direcciones; la cámara final aún no está definida.
- **Aviso de vigilancia:** animación, sonido o ambos antes de que el dueño se dé vuelta espontáneamente.
- **Esconderse tras el ruido:** definir si será una alternativa a quedarse quieto o una mecánica adicional.

## 🛠️ Tecnologías y estructura

- C++ y programación orientada a objetos.
- SFML 3 para ventana, gráficos y entrada de teclado.
- Visual Studio para el proyecto actual.

`GameProyect/main.cpp` contiene el bucle principal; `Personaje.h/.cpp` implementa el gato y su movimiento; `ObjetoChico.h/.cpp` inicia la representación de los objetos. Las imágenes están en `GameProyect/images/` y la distribución de SFML incluida en el repositorio está en `GameProyect/SFML/`.

## 🚀 Ejecutar el prototipo

En Windows, abrí `GameProyect.slnx` con Visual Studio, verificá la configuración de SFML 3 y compilá el proyecto. Ejecutalo con `GameProyect/` como directorio de trabajo: las texturas se cargan mediante rutas relativas, como `images/fondo.jpg`, `images/GatoNaranja.png` e `images/TazaCafe.png`.

La configuración de rutas de SFML en el proyecto de Visual Studio contiene rutas absolutas del equipo donde se creó. Si compilás en otra computadora, tendrás que ajustarlas a tu instalación o a la carpeta `GameProyect/SFML/`.

## 👨‍💻 Autor

Lisandro Romero — proyecto de aprendizaje de C++, SFML y desarrollo de videojuegos.
