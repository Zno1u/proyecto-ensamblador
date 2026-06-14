# BitQuest: Explorador de Matrices con C y NASM (64-bits)

**BitQuest** es un videojuego interactivo en consola desarrollado mediante **programación híbrida**, combinando la estructura lógica y la gestión de archivos en **C** junto a rutinas de bajo nivel en **Lenguaje Ensamblador (NASM x86-64)**. El motor del juego procesa mapas de gran escala almacenados en memoria y desplaza dinámicamente la perspectiva visual basándose en la posición del explorador.

---

## Características del Sistema y Código

### Mecánica del Laberinto e Interfaz Dinámica
El juego lee mapas de **60 filas por 60 columnas** desde archivos externos `.txt` (`nivelTutorial.txt`, `nivelFacil.txt`, etc.) cargando las posiciones de los muros y entidades directo a la matriz global `mapaActual[60][60]`. 
* **Ventana Móvil de 20x20**: En lugar de renderizar el mapa completo, la función `imprimirMapa` calcula cuadrantes rígidos de `20x20` basados en los límites de la posición del jugador (`p->filaPersonaje` y `p->columnaPersonaje`), provocando un desplazamiento automático de la cámara en pantalla al cruzar los umbrales de las coordenadas.
* **Gráficos Avanzados y Colores**: El renderizado gráfico implementa caracteres extendidos y bloques ASCII (`█`, `░`, `©`, `≡`, `┼`) potenciados mediante secuencias de escape ANSI virtuales en la consola de Windows para pintar paredes, fondos, llaves y monedas con colores temáticos de alto contraste.

### Entidades del Entorno
* `P` / `█` : **Jugador** -> Posición actual del personaje dentro del laberinto.
* `#` / `█` : **Pared** -> Bloque físico infranqueable calculado por el motor.
* `.` / `░` : **Camino Libre** -> Superficie transitable por el jugador.
* `M` / `©` : **Moneda** -> Almacena y computa cuántas monedas quedan dinámicamente en el mapa.
* `K` / `┼` : **Llave** -> Activa el estado `g_llaveObtenida = true` indispensable para cruzar compuertas.
* `D` / `≡` : **Puerta** -> Barrera infranqueable que se desbloquea únicamente si el jugador posee la llave.
* `E` : **Salida** -> Activa el estado de victoria (`g_ganado = true`) para desplegar el resumen del nivel.

---

##  Controles del Juego

La captura de teclado se realiza mediante la librería nativa `conio.h` de Windows evaluando caracteres ASCII en tiempo real:
* **`W`** : Mover personaje hacia Arriba.
* **`A`** : Mover personaje hacia la Izquierda.
* **`S`** : Mover personaje hacia Abajo.
* **`D`** : Mover personaje hacia la Derecha.

---

##  Distribución del Repositorio

* `main.c`       : Flujo de control, inicialización de manejadores VT-100 para la consola y menú interactivo de selección de dificultades.
* `juego.c`      : Motor gráfico de la ventana 20x20, llamadas a las funciones híbridas y validaciones de estados globales.
* `juego.h`      : Encabezado con la estructura de datos `Personaje`, constantes de color ANSI, caracteres extendidos y firmas de enlace cruzado entre C y NASM.
* `procesos.asm` : Código fuente nativo en ensamblador x86-64 para el procesamiento avanzado de arreglos bidimensionales.
* `compilar.bat`    : Archivo de procesamiento por lotes para compilar todo el sistema con un solo comando en Windows.
* `*.txt`        : Archivos de configuración de los niveles (`nivelTutorial.txt`, `nivelFacil.txt`, `nivelMedio.txt`, `nivelDificil.txt`).

---

##  Compilación y Ejecución Automatizada

El proyecto está diseñado para ser compilado bajo entornos Windows de 64 bits utilizando **GCC** y **NASM**.
Ejecutar el script para la automatización del compilado (./compilar.bat) y para jugar ejecutar (./proyecto-ensamblador.exe).