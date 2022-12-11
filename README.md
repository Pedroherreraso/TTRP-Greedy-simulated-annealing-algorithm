# TTRP-Greedy-simulated-annealing-algorithm

## Descripcion del problema

Truck and trailer routing problem tiene su explicacion en los siguientes links:

- https://www.sciencedirect.com/science/article/pii/S0305054800000563
- https://www.sciencedirect.com/science/article/pii/S0305054812001724

Implemente 2 tipos de algoritmos, Simulated Annealing con alguna mejora y el algoritmo Greedy.

## Uso
Para que el algoritmo fucione las instancias de prueba solo pueden ser numeros enteros 

```make```

```./TTRP "ubicacion del archivo" "numero de iteraciones con las que si o si termina el algoritmo Simulated Annealing" "Temperatura inicial del Simulated Annealing" ```

Ejemplo:

``` ./TTRP instances/TTRP_01.txt 100 100 ```

# IMPORTANTE

Cabe destacar que el algoritmo de simulated annealing puede terminar antes ya que se escogido como disminuye la temperatura de manera aleatoria

# CONSIDERACIONES

El ouput del programa es de la siguiente forma:

vehicle  tour: 0 46 12 47 4 17 37 15 0   67.8km
vehicle  tour: 0 1 2 16 50 9 30 10 0  92.1km
vehicle  tour: 0 7 23 43 13 41 45 0 123.8km
vehicle  tour: 0 44 42 19 40 33 39 21 29 0  173.1km
vehicle  tour: 0 34 20 35 36 3 0  114.9km
trailer  tour: 0 27 32 11 38 5 49 0  66.3km
trailer  tour: 0 6 48 8 26 31 28 22 0  84.0km
trailer  tour: 0 18 14 25 24 0  70.6km

Costo/Distancia total de viaje:792.6km 

iteraciones realizadas 57
42.2ms    