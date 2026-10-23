#include <iostream>
#include "ListaDobleCircular.h"

using namespace std;

int main() {
    ListaDobleCircular lista;

    // Pruebas de insercion
    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);

    cout << "ESTADO INICIAL" << endl;
    lista.imprimir();

    cout << "\nBUSCANDO EL 30" << endl;
    lista.buscar(30);

    cout << "\nELIMINANDO UN VALOR EN MEDIO (20)" << endl;
    lista.eliminar(20);
    lista.imprimir();

    cout << "\nELIMINANDO LA CABEZA (10)" << endl;
    lista.eliminar(10);
    lista.imprimir();

    return 0;
}