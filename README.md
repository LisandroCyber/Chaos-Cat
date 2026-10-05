# Chaos Cat

Chaos Cat es un juego 2D en pixel art desarrollado en C++ con SFML. Controlás a un gato que puede recorrer una habitación, saltar sobre muebles y tirar objetos para causar un desastre.

Este README describe el estado actual de la rama `CambioMau`: un prototipo jugable con un nivel de cocina, movimiento, colisiones, sonidos y menús.

## Funciones implementadas

- Menú principal con imagen de fondo y opciones **Jugar** y **Salir**.
- Menú de pausa con **Continuar** y **Salir**, sobre la partida oscurecida con una capa semitransparente.
- Confirmación de salida con **Sí** y **No**, tanto al elegir Salir como al cerrar con la X. No aparece seleccionado inicialmente.
- La actualización de la partida se detiene en los menús y durante la confirmación.
- Música de fondo en bucle: comienza al jugar, se pausa en la pausa y en la confirmación, y continúa al regresar a la partida.
- Gato con animaciones de reposo, caminar, agacharse, saltar, sentarse y golpear.
- Nivel de cocina con dueño visible, heladera, mesa, superficie fija y cuatro objetos: taza, frutero, cacerola y torre de platos.
- Golpe del gato con efecto de sonido.
- Objetos que se pueden tirar, caen por gravedad y permanecen visibles en el borde inferior de la ventana.
- Sonido de impacto al llegar al piso, reproducido una sola vez por caída.
- Reinicio de los objetos y visualización de hitboxes para depuración.

## Controles

### Durante la partida

| Tecla | Acción |
|---|---|
| A / D | Moverse a izquierda / derecha |
| Shift izquierdo + A / D | Correr |
| Ctrl izquierdo | Agacharse; con A / D, desplazarse lentamente |
| Espacio | Saltar cuando el gato está apoyado |
| E | Golpear cuando está apoyado y no está realizando otro golpe |
| Escape | Pausar o continuar |
| R | Devolver todos los objetos a sus posiciones iniciales |
| M | Mostrar la posición del gato en la consola |

### Menús y confirmación

| Tecla | Acción |
|---|---|
| Flechas arriba / abajo | Elegir una opción del menú |
| Enter | Confirmar la opción |
| Flechas izquierda / derecha | Elegir Sí o No en la confirmación de salida |
| Escape | Cancelar la confirmación |

## Mecánicas y física

### Gato y plataformas

El movimiento horizontal y la gravedad se calculan en cada actualización. El salto comienza con velocidad vertical negativa y la gravedad la aumenta hasta producir la caída.

Los muebles y las superficies fijas funcionan como plataformas: el gato puede atravesarlos desde abajo y apoyarse al descender. El apoyo se detecta comparando la base del gato en la actualización anterior con su posición actual. Si deja de tener una superficie debajo, comienza a caer.

El cuerpo del gato usa una hitbox fija de **74 × 110 píxeles**, independiente de la animación. El ataque tiene otra hitbox, ubicada hacia el lado al que mira.

### Objetos

Los objetos que todavía no fueron tirados bloquean lateralmente al gato y pueden servir de apoyo. Un golpe frontal o un golpe desde arriba puede lanzarlos.

Al tirarlos reciben velocidad horizontal según la dirección del golpe y un impulso hacia arriba. Luego caen por gravedad. Sus posiciones se corrigen en los bordes laterales de la ventana y su base queda alineada con el borde inferior al aterrizar.

Después del impacto se detienen. Permanecen marcados como tirados y dejan de participar en las colisiones con el gato. No hay rebotes, rotación, fragmentos ni colisiones de los objetos lanzados contra los muebles.

Todos los objetos usan actualmente el mismo sonido `sound effects/vidrioRoto.wav`; la imagen del objeto permanece intacta después de caer.

## Estado actual y pendientes

La idea final es causar caos en distintas habitaciones sin que el dueño descubra al gato. En esta rama, el dueño todavía es una representación gráfica: no se da vuelta, no detecta movimiento y no reacciona al ruido.

Quedan pendientes el tiempo límite, el objetivo de objetos por habitación, el puntaje, las condiciones de victoria y derrota, más niveles, posiciones aleatorias, configuración de controles y audio, y los modos adicionales.

## Integrantes

- Gunter Bonwit
- Mauricio Gutierres
- Lisandro Romero
