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

## Rama de desarrollo

El trabajo actual se realiza en la rama [`EnProceso`](https://github.com/LisandroCyber/Chaos-Cat/tree/EnProceso).

## ✅ Qué funciona hoy

- Ventana de 1280 × 720 con fondo, gato y una taza en pantalla.
- Movimiento del gato en cuatro direcciones con WASD, con opciones de correr y agacharse.
- Cambio de orientación horizontal del sprite y límites de movimiento dentro de la ventana.
- Carga de imágenes y clases separadas para el personaje y el objeto.
- Límite configurado de 144 FPS.

La taza se dibuja en pantalla, pero **todavía no se puede empujar ni tirar**. Tampoco hay dueño, niveles, temporizador, detección, sonido ni puntaje funcionales.

### Decisiones abiertas

- **Perspectiva visual:** vista desde arriba o de frente. El prototipo actual usa movimiento en cuatro direcciones; la cámara final aún no está definida.
- **Aviso de vigilancia:** animación, sonido o ambos antes de que el dueño se dé vuelta espontáneamente.
- **Esconderse tras el ruido:** definir si será una alternativa a quedarse quieto o una mecánica adicional.

## 🛠️ Tecnologías y estructura

- C++ y programación orientada a objetos.
- SFML 3 para ventana, gráficos y entrada de teclado.
- Visual Studio para el proyecto actual.

## 👨‍💻 Autor

Lisandro Romero — proyecto de aprendizaje de C++, SFML y desarrollo de videojuegos.
