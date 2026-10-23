/***********************************************************************
 * Module:  ListaDobleCircular.cpp
 * Author:  IdeaPad Gaming
 * Modified: viernes, 23 de octubre de 2026 9:51:05
 * Purpose: Implementation of the class ListaDobleCircular
 ***********************************************************************/

#include "Nodo.h"
#include "ListaDobleCircular.h"
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////
// Name:       ListaDobleCircular::insertar(int valor)
// Purpose:    Implementation of ListaDobleCircular::insertar()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////
ListaDobleCircular::ListaDobleCircular() {
    cabeza = nullptr;
}

void ListaDobleCircular::insertar(int valor)
{
   Nodo* nuevo = new Nodo(valor);
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* cola = cabeza->anterior;
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDobleCircular::eliminar(int valor)
// Purpose:    Implementation of ListaDobleCircular::eliminar()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaDobleCircular::eliminar(int valor)
{
   if (!cabeza) {
        cout << "La lista esta vacia. No hay elementos para eliminar.\n";
        return;
    }

    Nodo* actual = cabeza;
    bool encontrado = false;

    // 1. Buscar el nodo que contiene el valor
    do {
        if (actual->dato == valor) {
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (!encontrado) {
        cout << "El valor " << valor << " no se encuentra en la lista.\n";
        return;
    }

    // 2. CASO 1: La lista tiene un solo nodo y coincide
    if (cabeza->siguiente == cabeza && cabeza->dato == valor) {
        delete cabeza;
        cabeza = nullptr;
        cout << "Elemento " << valor << " eliminado. La lista ahora esta vacia.\n";
        return;
    }

    // 3. CASO 2: El nodo a eliminar es la cabeza actual
    if (actual == cabeza) {
        Nodo* cola = cabeza->anterior;
        cabeza = cabeza->siguiente;
        cola->siguiente = cabeza;
        cabeza->anterior = cola;
        delete actual;
    }
    // 4. CASO 3: El nodo está en el medio o es la cola
    else {
        Nodo* anteriorNodo = actual->anterior;
        Nodo* siguienteNodo = actual->siguiente;

        anteriorNodo->siguiente = siguienteNodo;
        siguienteNodo->anterior = anteriorNodo;
        delete actual;
    }

    cout << "Elemento " << valor << " eliminado correctamente.\n";
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDobleCircular::buscar(int valor)
// Purpose:    Implementation of ListaDobleCircular::buscar()
// Parameters:
// - valor
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaDobleCircular::buscar(int valor)
{
   if (!cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    Nodo* actual = cabeza;
    int pos = 0;
    do {
        if (actual->dato == valor) {
            cout << "Elemento " << valor << " encontrado en la posicion " << pos << ".\n";
            return;
        }
        actual = actual->siguiente;
        pos++;
    } while (actual != cabeza);
    cout << "Elemento " << valor << " no encontrado.\n";
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDobleCircular::imprimir()
// Purpose:    Implementation of ListaDobleCircular::imprimir()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaDobleCircular::imprimir(void)
{
   if (!cabeza) {
        cout << "Lista vacia." << endl;
        return;
    }
    Nodo* actual = cabeza;
    cout << "Lista: ";
    do {
        cout << "[" << actual->dato << "] <-> ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    cout << "(vuelve al inicio)" << endl;
}