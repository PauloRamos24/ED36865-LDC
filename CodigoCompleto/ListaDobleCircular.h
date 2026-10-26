/***********************************************************************
 * Module:  ListaDobleCircular.h
 * Author:  IdeaPad Gaming
 * Modified: viernes, 23 de octubre de 2026 9:51:05
 * Purpose: Declaration of the class ListaDobleCircular
 ***********************************************************************/

#if !defined(__ListasDoblesEliminar_ListaDobleCircular_h)
#define __ListasDoblesEliminar_ListaDobleCircular_h

#include "Nodo.h"

class ListaDobleCircular
{
public:
    ListaDobleCircular();

    void insertar(int valor);
    void eliminar(int valor);
    void buscar(int valor);
    void imprimir();

private:
    Nodo<int>* cabeza;
};

#endif