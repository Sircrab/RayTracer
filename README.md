# RayTracer
RayTracer para CC7615

De momento, debido a dependencias de librerias para JPEG el proyecto solo esta funcionando en Linux.
Si existen problemas de dependencias descargar la libreria libjpeg-dev

Junto con los parametros ya existentes se añaden 2 más:

-n [numero de hilos] (por defecto 1)

-t [tamaño del task] (por defecto 1)

El número de hilos indica en cuantos hilos se lanzara el renderer.
El tamaño del task indica la granulosidad de cada tarea que cada hilo
realiza, de la forma t X t

Ejemplo: -n 8 -t 3:
El programa corre en 8 hilos en donde cada hilo resuelve por pasada un
"Pedazo" de la imagen final de tamaño 3 X 3
