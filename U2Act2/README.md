# PRT-7 Decoder (Arduino, CMake + MinGW)

Proyecto simple para decodificar el protocolo PRT-7 desde un Arduino real (no simulado).

## Compilar en Windows (MinGW)

1. Instala MinGW (g++), CMake y asegúrate de que `mingw32-make.exe` esté en el PATH.
2. Desde una terminal PowerShell:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

Esto generará el ejecutable `prt7` (o `prt7.exe`) dentro de `build/`.

## Ejecutar

Conecta el Arduino y verifica el puerto (por ejemplo `COM3`). Luego (el programa queda escuchando indefinidamente; detén con Ctrl+C):

```
./prt7 COM3 9600
```

Argumentos:
- Primer argumento: nombre del puerto (p.ej. `COM3`). Si tu puerto es mayor a `COM9`, usa la notación `\\.\COM10`.
- Segundo argumento: baud rate (por defecto 9600).

## Protocolo esperado
Líneas tipo `L,X` o `M,N` (con `\n` entre líneas). Ejemplo del Arduino:

```
L,H
L,O
L,L
M,2
L,A
L,Space
L,W
M,-2
L,O
L,R
L,L
L,D
```

## Notas
- No se usa STL (ni `std::string`, `std::vector`, etc.).
- Estructuras de datos manuales: lista doble para la carga y lista circular para el rotor.
- Comunicación serial con Win32 API (`CreateFile`, `ReadFile`, `DCB`, etc.).

## Documentación
Se incluyen comentarios tipo Doxygen. Si tienes Doxygen instalado, puedes generar docs ejecutando en la raíz del proyecto:

```
doxygen Doxyfile
```
