# Documentación: Lista Doblemente Enlazada Circular en C++

> Análisis de las operaciones **Insertar**, **Eliminar**, **Imprimir** y **Buscar**
> a partir de los archivos `listasdoblecircular.cpp`, `eliminar.cpp`, `imprimir.cpp` y `buscar.cpp`.

---

## Índice

0. [Conceptos previos](#0-conceptos-previos)
1. [Insertar](#1-insertar)
2. [Eliminar](#2-eliminar)
3. [Imprimir](#3-imprimir)
4. [Buscar](#4-buscar)
5. [Resumen comparativo](#5-resumen-comparativo)
6. [Observaciones y mejoras sugeridas](#6-observaciones-y-mejoras-sugeridas)

---

## 0. Conceptos previos

### 0.1 ¿Qué estructura implementan los archivos?

Aunque el enunciado habla de una *lista doblemente enlazada*, el código implementa una variante más específica: una **lista doblemente enlazada CIRCULAR**. La diferencia es clave:

| Característica | Doble lineal (clásica) | **Doble circular (este código)** |
|---|---|---|
| `primero->anterior` | `NULL` | **apunta al último nodo** |
| `ultimo->siguiente` | `NULL` | **apunta al primer nodo** |
| ¿Existe `NULL` en los extremos? | Sí | **No** (solo si la lista está vacía) |
| ¿Necesita puntero `tail`? | Sí, normalmente | **No**: `tail = cabeza->anterior` |
| Condición de parada al recorrer | `actual != NULL` | `actual != cabeza` (volver al inicio) |

### 0.2 El nodo

```cpp
class Nodo {
public:
    int dato;          // información almacenada
    Nodo* siguiente;   // "next": nodo que viene después
    Nodo* anterior;    // "prev": nodo que viene antes
};
```

En `listasdoblecircular.cpp` el nodo y la lista son **plantillas** (`template <typename T>`), por lo que pueden almacenar cualquier tipo. En los demás archivos `T` es simplemente `int`.

### 0.3 Equivalencia de nombres (código ↔ diagramas)

| En el código C++ | En la teoría / diagramas | Significado |
|---|---|---|
| `cabeza` | `head` | Primer nodo de la lista |
| `cabeza->anterior` | `tail` | **Último nodo** (no hay puntero `tail` aparte) |
| `siguiente` | `next` | Enlace hacia adelante |
| `anterior` | `prev` | Enlace hacia atrás |
| `nuevo` | `nuevo` | Nodo recién creado con `new` |
| `ultimo` | `tail` | Variable local = `cabeza->anterior` |
| `actual` | `aux` | Puntero de recorrido |

### 0.4 Notación de los diagramas

Cada nodo se dibuja así:

```
[ ant | DATO | sig ]
```

Los enlaces entre nodos consecutivos se dibujan con `<->`. Como la lista es circular, **debajo de cada diagrama** se indica el "cierre del círculo":

```
cabeza
  |
  v
[ ant | 10 | sig ] <-> [ ant | 20 | sig ] <-> [ ant | 30 | sig ]
  ^                                                         |
  |                                                         |
  +--- ant de 10 apunta a 30       sig de 30 apunta a 10 ---+
```

Es decir, la lista real es un **anillo**:

```
        +--------------------------------------+
        |                                      |
        v                                      |
     [ 10 ] <-----> [ 20 ] <-----> [ 30 ] ----+
        ^                                      |
        +--------------------------------------+
           (el "ant" de 10 apunta a 30)
```

> **Convención:** en los diagramas de las secciones siguientes se usa una forma compacta:
> `(<-)` significa "el `anterior` del primero apunta al último" y `(->)` significa "el `siguiente` del último apunta al primero".

### 0.5 Estado de la lista vacía

```
cabeza = NULL        (no hay ningún nodo)
```

---

## 1. Insertar

> Archivo: `listasdoblecircular.cpp`
> Funciones: `insertarAlFinal(T valor)` e `insertarAlInicio(T valor)`

### 1.1 Propósito de la operación

| | `insertarAlFinal` | `insertarAlInicio` |
|---|---|---|
| **Qué hace** | Agrega un nodo nuevo como **último** elemento | Agrega un nodo nuevo como **primer** elemento |
| **Parámetro** | `T valor`: dato a almacenar | `T valor`: dato a almacenar |
| **Retorno** | `void` (no devuelve nada) | `void` (no devuelve nada) |
| **Efecto sobre `cabeza`** | Solo cambia si la lista estaba vacía | **Siempre** cambia: `cabeza = nuevo` |
| **Efecto sobre `tamanio`** | `tamanio++` | `tamanio++` |
| **Complejidad** | **O(1)** | **O(1)** |

> **Dato clave:** ambas son O(1) gracias a la circularidad. Como el último nodo es `cabeza->anterior`, no hace falta recorrer la lista para llegar al final.

### 1.2 Diagrama gráfico

Partimos de una lista con tres elementos: **10, 20, 30**.

#### A) `insertarAlFinal(40)`

**ANTES**

```
cabeza
  |
  v
[ 30 | 10 | 20 ] <-> [ 10 | 20 | 30 ] <-> [ 20 | 30 | 10 ]
                                                   ^
                                                   |
                                  ultimo = cabeza->anterior   (nodo 30)
```

> Aquí se muestra el contenido real de los punteros: el nodo `10` tiene `ant=30` y `sig=20`; el nodo `30` tiene `ant=20` y `sig=10`.

**DURANTE (paso 1):** se crea `nuevo` y se enlaza hacia los extremos actuales, pero **nadie lo apunta aún**.

```
                         nuevo
                           |
                           v
                    [ 30 | 40 | 10 ]
                      |         |
         anterior = ultimo     siguiente = cabeza
                      |         |
                      v         v
 cabeza -> [10] <-> [20] <-> [30]      (la lista original sigue intacta)
```

**DURANTE (paso 2):** se "cose" el nodo en la lista modificando los dos nodos vecinos.

```
   ultimo->siguiente = nuevo        cabeza->anterior = nuevo

 cabeza
   |
   v
 [ 40 | 10 | 20 ] <-> [ 10 | 20 | 30 ] <-> [ 20 | 30 | 40 ] <-> [ 30 | 40 | 10 ]
   ^                                                                    |
   |                                                                    |
   +------------------ sig de 40 apunta a 10 ---------------------------+
```

**DESPUÉS**

```
cabeza
  |
  v
[ ant | 10 | sig ] <-> [ ant | 20 | sig ] <-> [ ant | 30 | sig ] <-> [ ant | 40 | sig ]
  ^                                                                          |
  |  (<-) ant de 10 = 40                              (->) sig de 40 = 10    |
  +--------------------------------------------------------------------------+

tamanio = 4        cabeza NO cambió
```

---

#### B) `insertarAlInicio(5)`

**ANTES**

```
cabeza
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]        ultimo = cabeza->anterior = 30
  ^                       |
  +-----------------------+
```

**DURANTE:** `nuevo` se conecta entre `ultimo` (30) y `cabeza` (10). Es **el mismo enlazado** que al final...

```
  ultimo             nuevo              cabeza
    |                  |                  |
    v                  v                  v
  [ 30 ] <-------> [  5  ] <-------> [ 10 ] <-> [ 20 ]
    ^                                                |
    +------------ (sig de 30 apunta ahora a 5)       |
                  (ant de 10 apunta ahora a 5)       |
```

**DESPUÉS:** ...y la **única diferencia** es la última línea: `cabeza = nuevo`.

```
cabeza (movida)
  |
  v
[ 5 ] <-> [ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^                               |
  | (<-) ant de 5 = 30            |
  +-------------------------------+  (->) sig de 30 = 5

tamanio = 4        cabeza AHORA apunta a 5
```

> **Idea para recordar:** insertar al inicio y al final es *exactamente lo mismo* en una lista circular. Lo único que cambia es si `cabeza` se mueve (inicio) o se queda (final).

### 1.3 Explicación paso a paso del código

#### `insertarAlFinal`

```cpp
void insertarAlFinal(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);   // (1)

    if (estaVacia()) {                      // (2)
        nuevo->siguiente = nuevo;           // (3)
        nuevo->anterior = nuevo;            // (4)
        cabeza = nuevo;                     // (5)
    } else {
        Nodo<T>* ultimo = cabeza->anterior; // (6)

        nuevo->siguiente = cabeza;          // (7)
        nuevo->anterior = ultimo;           // (8)
        ultimo->siguiente = nuevo;          // (9)
        cabeza->anterior = nuevo;           // (10)
    }
    tamanio++;                              // (11)
}
```

| # | Línea | Qué ocurre en memoria |
|---|---|---|
| 1 | `new Nodo<T>(valor)` | Se reserva memoria en el *heap*. El constructor deja `siguiente = anterior = nullptr`. El nodo está "flotando", aún no pertenece a la lista. |
| 2 | `estaVacia()` | Devuelve `cabeza == nullptr`. Decide cuál de los dos caminos seguir. |
| 3-4 | `nuevo->siguiente/anterior = nuevo` | **Lista vacía:** el nodo se apunta **a sí mismo** en ambas direcciones. Es la forma mínima de un anillo (círculo de 1 elemento). |
| 5 | `cabeza = nuevo` | El único nodo pasa a ser la cabeza. |
| 6 | `ultimo = cabeza->anterior` | Se obtiene el último nodo **en O(1)**, sin recorrer. |
| 7 | `nuevo->siguiente = cabeza` | El nuevo apunta hacia adelante al primero (cierra el círculo). |
| 8 | `nuevo->anterior = ultimo` | El nuevo apunta hacia atrás al antiguo último. |
| 9 | `ultimo->siguiente = nuevo` | El antiguo último ahora apunta adelante al nuevo. |
| 10 | `cabeza->anterior = nuevo` | La cabeza ahora apunta hacia atrás al nuevo (cierra el círculo por el otro lado). |
| 11 | `tamanio++` | Se actualiza el contador. |

> **El orden importa:** primero se configuran los punteros del `nuevo` (líneas 7-8) y *después* se modifican los nodos existentes (9-10). Así, si algo fallara en medio, la lista original no queda rota.

#### `insertarAlInicio`

```cpp
void insertarAlInicio(T valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        Nodo<T>* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    cabeza = nuevo;   // <-- LA ÚNICA DIFERENCIA
    tamanio++;
}
```

Observa que `cabeza = nuevo;` está **fuera** del `if/else`, porque en ambos casos (lista vacía o no) el nodo nuevo debe convertirse en la cabeza.

### 1.4 Casos borde

| Escenario | `insertarAlFinal` | `insertarAlInicio` |
|---|---|---|
| **Lista vacía** (`cabeza == NULL`) | Entra al `if`. El nodo se autoapunta y `cabeza = nuevo`. | Entra al `if`. El nodo se autoapunta; luego `cabeza = nuevo`. |
| **Un solo elemento** | `ultimo = cabeza->anterior` es la propia cabeza. Se enlaza correctamente (ver diagrama abajo). | Igual: `ultimo` y `cabeza` son el mismo nodo, y el resultado es correcto. |
| **Extremo final** | Es el caso normal de esta función. | `nuevo` queda antes de la cabeza y se convierte en ella. |
| **Extremo inicial** | `cabeza` no cambia. | Es el caso normal de esta función. |
| **Elemento no encontrado** | *No aplica a inserción.* | *No aplica a inserción.* |

**Diagrama: insertar en lista de un solo elemento** (`insertarAlFinal(20)` con la lista `[10]`)

```
ANTES:                       cabeza
                               |
                               v
                       +--> [ 10 ] --+       ant = sig = el mismo nodo
                       +-----<------+       ultimo = cabeza->anterior = 10

DESPUÉS:                     cabeza
                               |
                               v
                            [ 10 ] <-----> [ 20 ]
                               ^              |
                               +--------------+
                    sig de 10 = 20, ant de 10 = 20
                    sig de 20 = 10, ant de 20 = 10
```

> Este caso funciona **sin ningún `if` especial** porque `ultimo == cabeza`, así que las líneas 9 y 10 modifican el mismo nodo (`sig` y `ant` respectivamente) y el resultado sigue siendo un anillo válido de 2 nodos.

---

## 2. Eliminar

> Archivo: `eliminar.cpp`
> Función: `void eliminar(int dato)`

### 2.1 Propósito de la operación

| | |
|---|---|
| **Qué hace** | Busca el **primer** nodo cuyo `dato` coincide y lo elimina de la lista, liberando su memoria. |
| **Parámetro** | `int dato`: valor que se desea eliminar. |
| **Retorno** | `void`. El resultado se informa por consola: `"Elemento eliminado"`, `"Elemento no encontrado"` o `"La lista esta vacia"`. |
| **Complejidad** | **O(n)** en el peor caso (hay que recorrer para encontrarlo). El desenlace del nodo en sí es O(1). |
| **Duplicados** | Solo elimina la **primera** coincidencia (porque hace `return` al encontrarla). |

### 2.2 Diagrama gráfico

Lista inicial: **10, 20, 30**.

#### A) Eliminar un nodo del medio: `eliminar(20)`

**ANTES**

```
cabeza
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]       (el círculo se cierra 30 -> 10 y 10 -> 30)
  ^
  |
actual (empieza en la cabeza)
```

**DURANTE (recorrido):** `actual` avanza hasta encontrar el dato.

```
Iteración 1:  actual -> [10]   10 == 20 ? NO   -> actual = actual->siguiente
Iteración 2:  actual -> [20]   20 == 20 ? SÍ   -> se elimina

cabeza                actual
  |                     |
  v                     v
[ 10 ] <-> [ 20 ] <-> [ 30 ]
```
*(en la iteración 2, `actual` está sobre el nodo `20`)*

**DURANTE (desenlace):** se "saltea" el nodo `actual`.

```
actual->anterior->siguiente = actual->siguiente;   // 10.sig  -> 30
actual->siguiente->anterior = actual->anterior;    // 30.ant  -> 10

              +-----------------------------+
              |      (nuevo enlace)         |
              v                             |
          [ 10 ] ------------------------> [ 30 ]
              ^  <-----------------------     |
              |                               |
              +-----------------------------+

          [ 20 ]   <- actual: ya nadie lo apunta, pero él aún apunta a 10 y 30
```

**DESPUÉS** (`delete actual`)

```
cabeza
  |
  v
[ 10 ] <-> [ 30 ]
  ^          |
  +----------+       (círculo de 2 nodos)

"Elemento eliminado"       El nodo 20 fue liberado de la memoria.
```

---

#### B) Eliminar la cabeza: `eliminar(10)`

**ANTES**

```
cabeza, actual
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^                      |
  +----------------------+
```

**DURANTE:** el dato coincide ya en la primera comparación.

```
1) actual->anterior->siguiente = actual->siguiente;   // 30.sig -> 20
2) actual->siguiente->anterior = actual->anterior;    // 20.ant -> 30
3) if (actual == cabeza) cabeza = actual->siguiente;  // cabeza -> 20

  actual (10)           cabeza (nueva)
     |                      |
     v                      v
   [ 10 ]  (aislado)     [ 20 ] <-> [ 30 ]
                            ^          |
                            +----------+
```

**DESPUÉS**

```
cabeza
  |
  v
[ 20 ] <-> [ 30 ]
  ^          |
  +----------+

"Elemento eliminado"
```

---

#### C) Eliminar el único nodo: `eliminar(10)` con la lista `[10]`

**ANTES**

```
cabeza, actual
  |
  v
+-> [ 10 ] --+      actual->siguiente == actual   (se apunta a sí mismo)
+-----<------+
```

**DESPUÉS**

```
cabeza = NULL        (lista vacía)

"Elemento eliminado"
```

### 2.3 Explicación paso a paso del código

```cpp
void eliminar(int dato) {
    if (cabeza == nullptr) {                          // (1)
        cout << "La lista esta vacia" << endl;
        return;
    }

    Nodo* actual = cabeza;                            // (2)

    do {                                              // (3)
        if (actual->dato == dato) {                   // (4)

            if (actual->siguiente == actual) {        // (5)
                cabeza = nullptr;                     // (6)
            } else {
                actual->anterior->siguiente = actual->siguiente;   // (7)
                actual->siguiente->anterior = actual->anterior;    // (8)

                if (actual == cabeza) {               // (9)
                    cabeza = actual->siguiente;       // (10)
                }
            }

            delete actual;                            // (11)
            cout << "Elemento eliminado" << endl;
            return;                                   // (12)
        }

        actual = actual->siguiente;                   // (13)

    } while (actual != cabeza);                       // (14)

    cout << "Elemento no encontrado" << endl;         // (15)
}
```

| # | Línea | Qué hace cada puntero |
|---|---|---|
| 1 | `cabeza == nullptr` | Protección: no se puede eliminar de una lista sin nodos. |
| 2 | `actual = cabeza` | `actual` (el `aux`) arranca en el primer nodo. |
| 3 | `do { ... }` | Se usa `do-while` para garantizar **al menos una** comparación (ver sección 3 para el motivo). |
| 4 | `actual->dato == dato` | Compara el nodo actual con el dato buscado. |
| 5 | `actual->siguiente == actual` | **Truco para detectar un solo nodo:** en un anillo de un nodo, el `siguiente` es el propio nodo. |
| 6 | `cabeza = nullptr` | La lista queda vacía. No hay vecinos que reenlazar. |
| 7 | `actual->anterior->siguiente = actual->siguiente` | El **vecino izquierdo** deja de apuntar a `actual` y apunta al **vecino derecho**. |
| 8 | `actual->siguiente->anterior = actual->anterior` | El **vecino derecho** deja de apuntar a `actual` y apunta al **vecino izquierdo**. |
| 9-10 | `if (actual == cabeza) cabeza = actual->siguiente` | Si se borró la cabeza, esta avanza al siguiente nodo. Se hace **después** de reenlazar, y `actual->siguiente` sigue siendo válido porque `actual` aún no fue liberado. |
| 11 | `delete actual` | Se libera la memoria del nodo ya desconectado. |
| 12 | `return` | Termina: solo se borra la primera coincidencia. |
| 13 | `actual = actual->siguiente` | Avanza al siguiente candidato. |
| 14 | `while (actual != cabeza)` | Condición de parada: se dio **una vuelta completa** al círculo. |
| 15 | `"Elemento no encontrado"` | Solo se alcanza si el bucle terminó sin encontrar el dato. |

> **Error clásico a evitar:** hacer `delete actual` *antes* de las líneas 7-10. Se estaría usando memoria liberada (*use-after-free*). El código lo hace en el orden correcto.

### 2.4 Casos borde

| Escenario | Comportamiento del código |
|---|---|
| **Lista vacía** (`cabeza == NULL`) | Imprime `"La lista esta vacia"` y hace `return` de inmediato (línea 1). No se accede a ningún puntero nulo. |
| **Un solo elemento (coincide)** | `actual->siguiente == actual` es verdadero → `cabeza = nullptr`. La lista vuelve al estado vacío. |
| **Un solo elemento (no coincide)** | Compara una vez, `actual = actual->siguiente` (vuelve a sí mismo), `actual == cabeza` → el bucle termina → `"Elemento no encontrado"`. |
| **Eliminar la cabeza** (varios nodos) | Reenlaza vecinos y mueve `cabeza = actual->siguiente`. El último nodo ahora apunta a la nueva cabeza. |
| **Eliminar el último nodo** | `actual->anterior->siguiente = actual->siguiente` hace que el penúltimo apunte a `cabeza`. La cabeza no cambia, pero su `anterior` pasa a ser el penúltimo. No requiere código especial. |
| **Elemento no encontrado** | Se recorre todo el anillo, `actual` vuelve a `cabeza`, el `while` termina y se imprime `"Elemento no encontrado"`. |
| **Valores duplicados** | Solo se elimina la primera ocurrencia (la más cercana a `cabeza`). |

**Diagrama: eliminar el último nodo** (`eliminar(30)` en `[10, 20, 30]`)

```
ANTES:   cabeza
           |
           v
         [ 10 ] <-> [ 20 ] <-> [ 30 ]     actual = 30
           ^                      |
           +----------------------+

PASO:    30.ant (20) .sig = 30.sig (10)   =>  20.sig -> 10
         30.sig (10) .ant = 30.ant (20)   =>  10.ant -> 20

DESPUÉS: cabeza
           |
           v
         [ 10 ] <-> [ 20 ]
           ^          |
           +----------+
```

---

## 3. Imprimir

> Archivo: `imprimir.cpp`
> Función: `void imprimir()`

### 3.1 Propósito de la operación

| | |
|---|---|
| **Qué hace** | Recorre la lista desde la cabeza hacia adelante y muestra cada `dato` separado por espacios. |
| **Parámetros** | Ninguno. |
| **Retorno** | `void`. Escribe en consola. Si la lista está vacía, imprime `"Lista vacia"`. |
| **Complejidad** | **O(n)**: visita cada nodo una vez. |
| **Modifica la lista** | **No.** Es una operación de solo lectura (`cabeza` no se toca). |

### 3.2 Diagrama gráfico

Lista: **10, 20, 30**. La salida esperada es `10 20 30`.

**ANTES** (`actual = cabeza`)

```
cabeza
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^
  |
actual

Salida:  (vacía)
```

**DURANTE: iteración 1** → imprime 10

```
[ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^
  actual           imprime: 10
                   actual = actual->siguiente
```

**DURANTE: iteración 2** → imprime 20

```
[ 10 ] <-> [ 20 ] <-> [ 30 ]
             ^
             actual    imprime: 10 20
                       actual = actual->siguiente
```

**DURANTE: iteración 3** → imprime 30

```
[ 10 ] <-> [ 20 ] <-> [ 30 ]
                        ^
                        actual    imprime: 10 20 30
                                  actual = actual->siguiente  (= 10, la cabeza)
```

**DESPUÉS** (se evalúa `actual != cabeza` → `10 != 10` es FALSO)

```
cabeza, actual
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]       el bucle termina: se dio la vuelta completa

Salida final:  10 20 30
```

### 3.3 Explicación paso a paso del código

```cpp
void imprimir() {
    if (cabeza == nullptr) {                 // (1)
        cout << "Lista vacia" << endl;
        return;
    }

    Nodo* actual = cabeza;                   // (2)

    do {                                     // (3)
        cout << actual->dato << " ";         // (4)
        actual = actual->siguiente;          // (5)
    } while (actual != cabeza);              // (6)

    cout << endl;                            // (7)
}
```

| # | Línea | Qué hace cada puntero |
|---|---|---|
| 1 | `cabeza == nullptr` | Evita desreferenciar un puntero nulo (`cabeza->dato` provocaría un fallo). |
| 2 | `actual = cabeza` | Se usa una **variable auxiliar** para recorrer. Si se avanzara la propia `cabeza`, se perdería el inicio de la lista. |
| 3 | `do {` | Entra al menos una vez al bucle (ver nota abajo). |
| 4 | `cout << actual->dato` | Lee el dato del nodo en el que está `actual`. |
| 5 | `actual = actual->siguiente` | Mueve `actual` un nodo hacia adelante. Tras el último nodo, "salta" a la cabeza gracias a la circularidad. |
| 6 | `while (actual != cabeza)` | Mientras no se haya regresado al punto de partida, se sigue. |
| 7 | `endl` | Salto de línea final. |

> **¿Por qué `do-while` y no `while`?**
> En una lista circular, `actual` **empieza** igual a `cabeza`. Con un `while (actual != cabeza)` la condición sería falsa desde el inicio y **no se imprimiría nada**. El `do-while` ejecuta primero el cuerpo y evalúa la condición después.

> **Peligro: bucle infinito.** Una lista circular **nunca** llega a `NULL`. Un recorrido con `while (actual != nullptr)` no terminaría jamás. La condición correcta es "volví a la cabeza".

### 3.4 Casos borde

| Escenario | Comportamiento del código |
|---|---|
| **Lista vacía** (`cabeza == NULL`) | Imprime `"Lista vacia"` y retorna. Nunca entra al `do-while`. |
| **Un solo elemento** | `actual` imprime el dato; luego `actual = actual->siguiente` apunta a sí mismo, que es la cabeza → el bucle termina. Salida: `10`. |
| **Operaciones en los extremos** | Primer nodo: se imprime en la primera iteración. Último nodo: se imprime en la última, y su `siguiente` (la cabeza) provoca la salida. Los extremos no necesitan tratamiento especial. |
| **Elemento no encontrado** | *No aplica a imprimir.* |

**Diagrama: imprimir con un solo elemento**

```
cabeza, actual
  |
  v
+-> [ 10 ] --+       iteración 1: imprime 10
+-----<------+       actual = actual->siguiente  =>  sigue siendo [10] = cabeza
                     (actual != cabeza) es FALSO  =>  fin

Salida:  10
```

---

## 4. Buscar

> Archivo: `buscar.cpp`
> Función: `Nodo* buscar(int dato)`

### 4.1 Propósito de la operación

| | |
|---|---|
| **Qué hace** | Localiza el **primer** nodo (desde la cabeza) cuyo `dato` es igual al valor buscado. |
| **Parámetro** | `int dato`: valor a localizar. |
| **Retorno** | `Nodo*`: **puntero al nodo** encontrado, o `nullptr` si no existe (o la lista está vacía). |
| **Complejidad** | **O(n)** en el peor caso; **O(1)** si el elemento está en la cabeza. |
| **Modifica la lista** | **No.** Solo lectura. |

> **Diferencia con `imprimir`:** `buscar` **devuelve** un resultado (el puntero al nodo) en lugar de escribir en pantalla. Quien la llama decide qué hacer con él (en `main` se imprime `encontrado->dato`).

### 4.2 Diagrama gráfico

Lista: **10, 20, 30**. Se busca `20`.

**ANTES**

```
cabeza
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^
  |
actual = cabeza                    Buscando: 20
```

**DURANTE: iteración 1** (10 ≠ 20)

```
[ 10 ] <-> [ 20 ] <-> [ 30 ]
  ^
  actual          ¿10 == 20? NO  -> actual = actual->siguiente
```

**DURANTE: iteración 2** (20 == 20, ¡encontrado!)

```
[ 10 ] <-> [ 20 ] <-> [ 30 ]
             ^
             actual       ¿20 == 20? SÍ  -> return actual
```

**DESPUÉS**

```
cabeza
  |
  v
[ 10 ] <-> [ 20 ] <-> [ 30 ]
             ^
             |
        encontrado  (el puntero devuelto a main)

La lista NO cambió.   Salida: "Elemento encontrado: 20"
```

**Caso "no encontrado": se busca `99`**

```
iter 1:  actual -> [10]  10 != 99
iter 2:  actual -> [20]  20 != 99
iter 3:  actual -> [30]  30 != 99
         actual = actual->siguiente = [10] = cabeza   -> while (actual != cabeza) es FALSO
         sale del bucle  ->  return nullptr

Salida: "Elemento no encontrado"
```

### 4.3 Explicación paso a paso del código

```cpp
Nodo* buscar(int dato) {
    if (cabeza == nullptr) {              // (1)
        return nullptr;
    }

    Nodo* actual = cabeza;                // (2)

    do {                                  // (3)
        if (actual->dato == dato) {       // (4)
            return actual;                // (5)
        }

        actual = actual->siguiente;       // (6)
    } while (actual != cabeza);           // (7)

    return nullptr;                       // (8)
}
```

| # | Línea | Qué hace cada puntero |
|---|---|---|
| 1 | `cabeza == nullptr` | Lista vacía → no hay nada que buscar; se devuelve `nullptr`. |
| 2 | `actual = cabeza` | Puntero de recorrido (`aux`) en el primer nodo. |
| 3 | `do {` | Garantiza revisar al menos la cabeza. |
| 4 | `actual->dato == dato` | Compara el dato del nodo actual con el buscado. |
| 5 | `return actual` | **Devuelve la dirección del nodo.** El llamador recibe acceso directo al nodo (puede leer o modificar `->dato`). |
| 6 | `actual = actual->siguiente` | Avanza al siguiente nodo. |
| 7 | `while (actual != cabeza)` | Termina tras dar una vuelta completa. |
| 8 | `return nullptr` | Se llega aquí solo si se recorrió todo el anillo sin coincidencia. |

**Uso en `main`:**

```cpp
Nodo* encontrado = lista.buscar(valor);

if (encontrado != nullptr) {
    cout << "Elemento encontrado: " << encontrado->dato << endl;
} else {
    cout << "Elemento no encontrado" << endl;
}
```

> **Siempre se debe verificar `!= nullptr`** antes de usar el puntero devuelto. Acceder a `encontrado->dato` si es `nullptr` produce un fallo en ejecución.

### 4.4 Casos borde

| Escenario | Comportamiento del código |
|---|---|
| **Lista vacía** (`cabeza == NULL`) | Devuelve `nullptr` inmediatamente (línea 1). |
| **Un solo elemento (coincide)** | Primera comparación exitosa → `return actual`. |
| **Un solo elemento (no coincide)** | Una comparación fallida; `actual = actual->siguiente` es la propia cabeza → el bucle termina → `nullptr`. |
| **Elemento en la cabeza** | Se encuentra en la primera iteración (mejor caso, O(1)). |
| **Elemento en el último nodo** | Se encuentra en la última iteración, justo antes de volver a la cabeza (peor caso con éxito, O(n)). |
| **Elemento no encontrado** | Tras una vuelta completa devuelve `nullptr`. **No** entra en bucle infinito gracias a la condición `actual != cabeza`. |
| **Valores duplicados** | Devuelve el **primero** que encuentre partiendo desde la cabeza. |

---

## 5. Resumen comparativo

| Operación | Función | Retorno | Complejidad | Modifica la lista | Puntero clave |
|---|---|---|---|---|---|
| **Insertar al final** | `insertarAlFinal(T)` | `void` | O(1) | Sí | `ultimo = cabeza->anterior` |
| **Insertar al inicio** | `insertarAlInicio(T)` | `void` | O(1) | Sí (mueve `cabeza`) | `ultimo` y `cabeza = nuevo` |
| **Eliminar** | `eliminar(int)` | `void` | O(n) | Sí | `actual->anterior` / `actual->siguiente` |
| **Imprimir** | `imprimir()` | `void` | O(n) | No | `actual` |
| **Buscar** | `buscar(int)` | `Nodo*` | O(n) | No | `actual` |

**Patrón común de recorrido en una lista circular:**

```cpp
Nodo* actual = cabeza;
do {
    // ... trabajar con actual ...
    actual = actual->siguiente;
} while (actual != cabeza);
```

Las tres operaciones de recorrido (`eliminar`, `imprimir`, `buscar`) usan exactamente este esqueleto, precedido de la verificación `cabeza == nullptr`.

---

## 6. Observaciones y mejoras sugeridas

Al analizar los cuatro archivos se detectaron puntos que conviene conocer (son útiles para estudiar y para mejorar el código):

1. **Los archivos no comparten una misma clase.** `listasdoblecircular.cpp` usa plantillas (`template <typename T>`), con `cabeza` privada y `tamanio`, mientras que `buscar.cpp`, `imprimir.cpp` y `eliminar.cpp` usan `int`, `cabeza` pública y **no tienen** método de inserción: en su `main` los nodos se enlazan **a mano**. Lo ideal sería unificar todo en una única clase `ListaDobleCircular<T>` con las cuatro operaciones.

2. **`eliminar` no actualiza `tamanio`** porque esa versión de la clase no lo tiene. Al unificar las clases, se debe hacer `tamanio--` dentro de la rama de eliminación exitosa.

3. **No hay destructor.** Los nodos creados con `new` nunca se liberan al terminar el programa (fuga de memoria). Un destructor sencillo sería:

   ```cpp
   ~ListaDobleCircular() {
       while (!estaVacia()) {
           eliminarPrimero();   // o equivalente que haga delete
       }
   }
   ```

4. **Las operaciones de lectura no son `const`.** `imprimir()`, `buscar()`, `estaVacia()` y `getTamanio()` no modifican la lista, por lo que sería buena práctica declararlas `const`.

5. **`eliminar` mezcla lógica y presentación.** Imprime mensajes con `cout` en lugar de devolver un `bool`. Devolver `true`/`false` hace la función reutilizable y más fácil de probar.

6. **En `insertarAlFinal`/`insertarAlInicio`** el código de enlace está duplicado. Se podría reutilizar: `insertarAlInicio` equivale a `insertarAlFinal` seguido de `cabeza = cabeza->anterior`.

---

*Fin del documento.*
