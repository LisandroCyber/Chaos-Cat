🐱 Chaos Cat

Chaos Cat es un videojuego 2D desarrollado en C++ utilizando SFML 3, como proyecto de aprendizaje y práctica de Programación Orientada a Objetos.

El jugador controla a un gato que se mueve por una mesa mientras interactúa con distintos objetos del escenario.

🚧 Proyecto en desarrollo — actualmente se están implementando y mejorando las mecánicas principales del juego.

🎮 Concepto

En Chaos Cat, el jugador controla a un gato con el objetivo de causar el mayor caos posible sobre una mesa.

El juego busca combinar movimiento, interacción con objetos y diferentes mecánicas de gameplay en una experiencia con estética de videojuego arcade.

La idea principal es que el gato pueda desplazarse por el escenario e interactuar con objetos que se encuentran sobre la mesa.

✨ Características actuales
🐱 Personaje controlable.
🎮 Movimiento en cuatro direcciones.
🏃 Diferentes velocidades de movimiento.
🐌 Modo agachado.
🔄 Cambio de orientación del personaje.
🧱 Límites de movimiento dentro del escenario.
🖼️ Carga de texturas e imágenes.
☕ Implementación inicial de objetos interactuables.
🎯 Sistema básico de posición y movimiento.
🖥️ Ventana de juego de 1280×720.
⚡ Límite de 144 FPS.

El personaje utiliza las teclas WASD para desplazarse, Shift para correr y Ctrl para moverse agachado.

🕹️ Controles
Tecla	Acción
W	Moverse hacia arriba
A	Moverse hacia la izquierda
S	Moverse hacia abajo
D	Moverse hacia la derecha
SHIFT	Correr
CTRL	Agacharse
M	Mostrar la posición del gato en consola
🛠️ Tecnologías
C++
SFML 3
Visual Studio
Programación Orientada a Objetos
Git / GitHub

SFML se utiliza para manejar principalmente:

Ventana del juego
Renderizado 2D
Sprites y texturas
Entrada del teclado
Bucle principal del juego
📂 Estructura del proyecto
GameProyect/
│
├── GameProyect/
│   ├── images/
│   │
│   ├── SFML/
│   │
│   ├── main.cpp
│   │
│   ├── Personaje.h
│   ├── Personaje.cpp
│   │
│   ├── ObjetoChico.h
│   ├── ObjetoChico.cpp
│   │
│   ├── GameProyect.vcxproj
│   └── GameProyect.vcxproj.filters
│
├── GameProyect.slnx
├── cat.png.png
├── .gitignore
└── README.md

La lógica del personaje está separada en Personaje.h y Personaje.cpp, mientras que los objetos del escenario cuentan con su propia clase ObjetoChico.

🧩 Programación Orientada a Objetos

El proyecto utiliza conceptos de POO para organizar las diferentes entidades del juego.

Personaje

La clase Personaje se encarga de representar al gato y controlar:

Su textura y sprite.
Su posición.
Su velocidad.
El movimiento.
La orientación del sprite.
Los límites del escenario.
Su renderizado.

La clase además hereda de sf::Drawable, permitiendo dibujar el personaje directamente mediante window.draw(gato).

ObjetoChico

ObjetoChico representa objetos que forman parte del escenario y que posteriormente podrán utilizarse para implementar las mecánicas de interacción del juego.

🚀 Cómo ejecutar el proyecto
Requisitos

Para ejecutar el proyecto necesitás:

Windows
Visual Studio
C++ instalado mediante Visual Studio
SFML 3
Ejecución
Clonar el repositorio:
git clone https://github.com/LisandroCyber/GameProyect.git
Abrir la solución:
GameProyect.slnx
Verificar que las dependencias de SFML 3 estén correctamente configuradas.
Compilar el proyecto.
Ejecutar desde Visual Studio.

⚠️ Las rutas de los recursos gráficos son relativas al directorio de ejecución. Por ejemplo, el fondo se carga desde images/fondo.jpg y el personaje desde images/GatoNaranja.png.

🗺️ Roadmap
✅ Implementado

Ventana principal

Renderizado del escenario

Carga de texturas

Personaje controlable

Movimiento WASD

Correr

Agacharse

Cambio de orientación

Límites del escenario

Primera implementación de objetos

🔨 En desarrollo

Interacción con objetos

Objetos que puedan caer de la mesa

Sistema de sonido

Sistema de detección del dueño

NPC dueño de la casa

Sistema de puntuación

Pantallas de inicio y Game Over

Más objetos interactuables

Mejoras visuales

Animaciones del gato

🎯 Objetivo del proyecto

Este proyecto tiene como objetivo poner en práctica conocimientos de:

C++
Programación Orientada a Objetos
Manejo de clases y objetos
Herencia
Encapsulamiento
Manejo de sprites y texturas
Entrada de usuario
Lógica de videojuegos
Organización de proyectos
Uso de Git y GitHub

Además, busca servir como proyecto práctico para continuar desarrollando conocimientos en programación y desarrollo de videojuegos.

👨‍💻 Autor

Lisandro Romero

Estudiante de Técnico Universitario en Programación — UTN FRGP.

Interesado principalmente en desarrollo de software, C++ y backend, utilizando proyectos personales como forma de continuar desarrollando experiencia práctica.

📌 Estado del proyecto

En desarrollo 🚧

Este repositorio se actualiza progresivamente a medida que se incorporan nuevas mecánicas y sistemas al juego.
