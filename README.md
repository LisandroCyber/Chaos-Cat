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

## Estructura del código

Los archivos de código y recursos están en `GameProyect/`.

| Archivo o clase | Responsabilidad |
|---|---|
| `main.cpp` | Crear y ejecutar el juego |
| `Juego` | Ventana, eventos, actualización, dibujo, estados de menú y confirmación de salida |
| `Menu` | Fuente, título, dos opciones y navegación común |
| `MenuPrincipal` | Menú inicial e imagen de fondo |
| `MenuPausa` | Título y opciones de pausa |
| `Personaje` | Gato, entrada, animaciones, salto, gravedad, ataque y sonidos |
| `Nivel` | Recursos del nivel, entidades, colisiones, hitboxes y música |
| `NivelCocina` | Composición y recursos del nivel de cocina |
| `Mueble` | Sprite y hitbox del mueble |
| `Objeto` | Lanzamiento, caída, impacto, sonido y reinicio |
| `Humano` | Representación gráfica del dueño |
| `Constantes.h` | Resolución, límite de FPS, velocidades, gravedad y tiempos |

### Recursos

- `images/`: fondos, personajes, muebles y objetos.
- `fonts/`: fuente del menú.
- `music/`: música de fondo.
- `sound effects/`: efectos de sonido.
- `SFML/`: cabeceras y bibliotecas incluidas en el proyecto.

## Compilación y ejecución

1. Clonar la rama:

   ```bash
   git clone --branch CambioMau https://github.com/LisandroCyber/Chaos-Cat.git
   ```

2. Abrir `GameProyect.slnx` en Visual Studio con las herramientas de desarrollo de escritorio en C++.
3. Seleccionar **x64**, en Debug o Release. Ambas configuraciones tienen las rutas de SFML configuradas y usan C++17.
4. El proyecto declara el toolset **v145**. Si no está instalado, instalarlo o adaptar el toolset a uno compatible con las bibliotecas utilizadas.
5. Ejecutar con `GameProyect/` como directorio de trabajo, porque los recursos se cargan mediante rutas relativas.
6. Al ejecutar fuera de Visual Studio, colocar las DLL correspondientes a la configuración junto al ejecutable, incluido `openal32.dll`, y conservar las carpetas de recursos en el directorio de trabajo.

La versión de SFML incluida es **2.5.0**. La ventana es de **1280 × 720** y el límite está configurado en **144 FPS**.

## Estado actual y pendientes

La idea final es causar caos en distintas habitaciones sin que el dueño descubra al gato. En esta rama, el dueño todavía es una representación gráfica: no se da vuelta, no detecta movimiento y no reacciona al ruido.

Quedan pendientes el tiempo límite, el objetivo de objetos por habitación, el puntaje, las condiciones de victoria y derrota, más niveles, posiciones aleatorias, configuración de controles y audio, y los modos adicionales.

Detalles técnicos a revisar:

- La física usa valores por actualización y todavía no se ajusta mediante delta time.
- Los relojes de animación siguen contando durante la pausa, aunque la partida deja de actualizarse.
- El sonido de salto intenta cargar un MP3; el código señala que esa carga falla y requiere revisar el formato.
- El código carga `fonts/starcatcher.ttf`, mientras el archivo guardado es `fonts/Starcatcher.ttf`. La diferencia de mayúsculas puede impedir la carga en sistemas que distinguen ambos nombres.
- Las hitboxes se muestran por defecto. Para ocultarlas, cambiar `_mostrarHitboxes` en `Nivel`.

## Integrantes

- Gunter Bonwit
- Mauricio Gutierres
- Lisandro Romero
