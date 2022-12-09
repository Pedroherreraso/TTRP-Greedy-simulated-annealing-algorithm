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