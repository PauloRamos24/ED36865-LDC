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
ListaDobleCircular::ListaDobleCircular()
{
    cabeza = nullptr;
}

void ListaDobleCircular::insertar(int valor)
{
    Nodo<int>* nuevo = new Nodo<int>(valor);

    if (cabeza == nullptr)
    {
        cabeza = nuevo;

        cabeza->setSiguiente(cabeza);
        cabeza->setAnterior(cabeza);
    }
    else
    {
        Nodo<int>* cola = cabeza->getAnterior();

        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);

        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
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
    if (cabeza == nullptr)
    {
        cout << "La lista esta vacia." << endl;
        return;
    }

    Nodo<int>* actual = cabeza;

    do
    {
        if (actual->getDato() == valor)
        {
            break;
        }

        actual = actual->getSiguiente();

    } while (actual != cabeza);

    if (actual->getDato() != valor)
    {
        cout << "El valor " << valor << " no se encuentra." << endl;
        return;
    }

    if (cabeza->getSiguiente() == cabeza)
    {
        delete cabeza;
        cabeza = nullptr;

        cout << "Elemento eliminado." << endl;
        return;
    }

    Nodo<int>* anterior = actual->getAnterior();
    Nodo<int>* siguiente = actual->getSiguiente();

    anterior->setSiguiente(siguiente);
    siguiente->setAnterior(anterior);

    if (actual == cabeza)
    {
        cabeza = siguiente;
    }

    delete actual;

    cout << "Elemento " << valor << " eliminado correctamente." << endl;
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
    if (cabeza == nullptr)
    {
        cout << "Lista vacia." << endl;
        return;
    }

    Nodo<int>* actual = cabeza;
    int posicion = 0;

    do
    {
        if (actual->getDato() == valor)
        {
            cout << "Elemento " << valor
                 << " encontrado en la posicion "
                 << posicion << "." << endl;
            return;
        }

        actual = actual->getSiguiente();
        posicion++;

    } while (actual != cabeza);

    cout << "Elemento " << valor << " no encontrado." << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDobleCircular::imprimir()
// Purpose:    Implementation of ListaDobleCircular::imprimir()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaDobleCircular::imprimir()
{
    if (cabeza == nullptr)
    {
        cout << "Lista vacia." << endl;
        return;
    }

    Nodo<int>* actual = cabeza;

    cout << "Lista: ";

    do
    {
        cout << "[" << actual->getDato() << "] <-> ";

        actual = actual->getSiguiente();

    } while (actual != cabeza);

    cout << "(vuelve al inicio)" << endl;
}