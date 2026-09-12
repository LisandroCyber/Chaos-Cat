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
