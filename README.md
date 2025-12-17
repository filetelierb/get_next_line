*Este proyecto ha sido creado como parte del currículo de 42 por fletelie*

**Descripción**

Este proyecto trata de un set de funciones (mini librería) que permiten leer linea a linea un documento al recibir un *file descriptor*. Adicionalmente, se creó una variación que permite leer multiples functiones usando un sistema de listas para mantener trazabilidad de los ficheros leidos y los almacenamientos temporales asociados a cada uno.

**Instrucciones**

Se sugiere crear un Makefile propio o bien incorporar estas funciones y prototipos en otra librería. Si se desea probar de manera independiente, puede crear un programa de prueba (un main.c por ejemplo), incorporar el header correspondiente (`#include "get_next_line.h"` para probar el proyecto principal y `#include "get_next_line_bonus.h"` para el bonus, se deben probar por separado ya que ambas librerías comparten funciones con el mismo nombre) y proceder a compilar usando los flags correspondientes. Por ejemplo `cc -Werror -Wall -Wextra get_next_line.c get_next_line_utils.c ...`.

**Recursos**

Me he apoyado principalmente en la documentación man, https://pubs.opengroup.org/ y en mis colegas.

Utilicé la IA para entender los errores que me iban apareciendo y así ir purificando el código de manera manual.

**Algoritmo**

Para la parte obligatoria he decidido crear un struct propio `t_handler` en combinación con una variable estática. Esto me permitió centralizar la información en más relevante en una sola variable de fácil acceso y que puede ser actualizada desde cualquier parte usando punteros. Además, creé una función limpiadora encargada de limpiar los campos del struct que se deseen o el struct en su totalidad ante cualquier fallo o final de lectura.

Para la parte bonus, mantuve el struct pero utilicé una estrategia de listas para agregar en serie los nuevos *file descriptors* y su data asociada, minimiazando así la cantidad de código a refactorizar.