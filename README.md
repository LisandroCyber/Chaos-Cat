# Chaos Cat 🐈

**Chaos Cat** es un videojuego arcade en 2D desarrollado en **C++** con **SFML 3**.

El jugador controla a un gato travieso dentro de una casa. Su objetivo será recorrer las habitaciones y tirar distintos objetos antes de que el dueño lo descubra.

> El proyecto se encuentra actualmente en desarrollo.

🎮 Cómo se jugará
El gato se moverá sobre la mesa de la habitación y empujará los objetos para hacerlos caer.
El dueño hará otras actividades, pero podrá darse vuelta en cualquier momento. Se evalúa avisar al jugador con una animación o un sonido antes de que mire.
Cuando un objeto caiga, hará ruido y el dueño se dará vuelta necesariamente.
Mientras el dueño esté mirando, el gato deberá permanecer quieto: si se mueve, será descubierto y perderá. Después de aproximadamente 3 segundos, el dueño volverá a su actividad.
Para completar un nivel, habrá que tirar los objetos requeridos antes de que se agote el tiempo, sin ser descubierto.
La idea es combinar el caos de tirar cosas con una mecánica de «quedarse inmóvil» en el momento justo.

## Estado actual

Todas las implementaciones y modificaciones se hacen en la rama `EnProceso`.

## ✅ Qué funciona hoy

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

### Decisiones abiertas

- **Perspectiva visual:** vista desde arriba o de frente. El prototipo actual usa movimiento en cuatro direcciones; la cámara final aún no está definida.
- **Aviso de vigilancia:** animación, sonido o ambos antes de que el dueño se dé vuelta espontáneamente.
- **Esconderse tras el ruido:** definir si será una alternativa a quedarse quieto o una mecánica adicional.

## 🛠️ Tecnologías y estructura

- C++ y programación orientada a objetos.
- SFML 3 para ventana, gráficos y entrada de teclado.
- Visual Studio para el proyecto actual.
