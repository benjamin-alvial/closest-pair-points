# closest-pair-points
Se implementa un algoritmo determinístico y un algoritmo aleatorizado para resolver el problema de encontrar en un conjunto de puntos aquel par más cercano. El algoritmo determinístico implementado es del tipo dividir para conquistar y el algoritmo aleatorizado está basado en hashing con tres implementaciones distintas: la familia universal usual, una familia más rápida y uso de primos de Mersenne (para más detalle, visitar https://users.dcc.uchile.cl/~gnavarro/apunte2.pdf, página 122).

## Experimento 1
En el primer experimento se estudia la distribución de tiempos de ejecución de los algoritmos para un mismo arreglo.

En `pipeline_exp1.c` está el flujo general de la generación de arreglos de puntos y la búsqueda del par más cercano. En él, se deben especificar los parámetros del problema.

- `N_ONE` es la primera cantidad de puntos a probar.
- `N_TWO` es la segunda cantidad de puntos a probar.
- `N_THREE` es la tercera cantidad de puntos a probar.
- `NUMBER_REPS` es la cantidad de repeticiones a probar para cada cantidad de puntos.

Se debe compilar y ejecutar `pipeline_exp1.c` con gcc, con la opción `-lm`:

```
$ gcc -o pipeline_exp1 pipeline_exp1.c -lm
$ ./pipeline_exp1
```

Al compilar y ejecutarse, se itera sobre los tres valores dados y:
- Se crea un arreglo de puntos aleatorios.
- Se itera sobre las repeticiones para realizar la búsqueda con los algoritmos.
- Se escribe en un archivo de texto la tupla que contiene la cantidad de puntos, el número de la repetición y los tiempos de ejecución de los algoritmos.

Los resultados quedan finalmente en `performance_results_1.txt` en la carpeta `results`.

## Experimento 2
En el segundo experimento se estudia el comportamiento de los tiempos de ejecución a medida que crece la cantidad de puntos.

En `pipeline_exp2.c` está el flujo general de la generación de arreglos de puntos y la búsqueda del par más cercano. En él, se deben especificar los parámetros del problema.

- `N_INITIAL` es la primera cantidad de puntos a probar.
- `N_FINAL` es la última cantidad de puntos a probar.
- `N_STEP` es el paso con el que se van probando cantidades desde `N_INITIAL` hasta `N_FINAL`.
- `NUMBER_REPS` es la cantidad de repeticiones a probar para cada cantidad de puntos.

Se debe compilar y ejecutar `pipeline_exp2.c` con gcc, con la opción `-lm`:

```
$ gcc -o pipeline_exp2 pipeline_exp2.c -lm
$ ./pipeline_exp2
```

Al compilar y ejecutarse, se itera sobre los valores de cantidad de puntos dados y:
- Se crea un arreglo de puntos aleatorios.
- Se itera sobre las repeticiones para realizar la búsqueda con los algoritmos.
- Se escribe en un archivo de texto la tupla que contiene la cantidad de puntos, el número de la repetición y los tiempos de ejecución de los algoritmos.

Los resultados quedan finalmente en `performance_results_2.txt` en la carpeta `results`.

## Experimento 3
En el tercer experimento se estudia la distribución de tiempos de ejecución de los algoritmos para arreglos distintos de tamaño fijo.

En `pipeline_exp3.c` está el flujo general de la generación de arreglos de puntos y la búsqueda del par más cercano. En él, se deben especificar los parámetros del problema.

- `FIXED_INPUT_SIZE` es la cantidad de puntos de los distintos arreglos a probar.
- `FIXED_INPUT_REPS` es la cantidad de repeticiones a probar para generar un arreglo y buscar.

Se debe compilar y ejecutar `pipeline_exp3.c` con gcc, con la opción `-lm`:

```
$ gcc -o pipeline_exp3 pipeline_exp3.c -lm
$ ./pipeline_exp3
```

Al compilar y ejecutarse, se itera sobre las repeticiones y:
- Se crea un arreglo de puntos aleatorios.
- Se realiza la búsqueda con los algoritmos.
- Se escribe en un archivo de texto la tupla que contiene el número de la repetición y los tiempos de ejecución de los algoritmos.

Los resultados quedan finalmente en `performance_results_3.txt` en la carpeta `results`.

## Resultados
En `plot_results.py` está la implementación para encontrar los gráficos de los resultados obtenidos anteriormente. Se deben especificar los mismos parámetros utilizados en la búsqueda original:

- `fixed_n_array` es una lista con las tres cantidades de puntos a probar, en el experimento 1.
- `NUMBER_REPS` es la cantidad de repeticiones del experimento 2.
- `FIXED_N` es la cantidad fija de puntos a probar en el experimento 3.


Se debe estar en la carpeta `results` y se debe ejecutar:

```
$ python3 plot_results.py
```