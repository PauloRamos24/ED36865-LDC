
#include <iostream>
using namespace std;

class Nodo {
public:
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int dato) {
        this->dato = dato;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

class ListaDobleCircular {
public:
    Nodo* cabeza;

    ListaDobleCircular() {
        cabeza = nullptr;
    }

    void imprimir() {
        if (cabeza == nullptr) {
            cout << "Lista vacia" << endl;
            return;
        }

        Nodo* actual = cabeza;

        do {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        } while (actual != cabeza);

        cout << endl;
    }
};

int main() {
    ListaDobleCircular lista;

    Nodo* n1 = new Nodo(10);
    Nodo* n2 = new Nodo(20);
    Nodo* n3 = new Nodo(30);

    lista.cabeza = n1;

    n1->siguiente = n2;
    n2->siguiente = n3;
    n3->siguiente = n1;

    n1->anterior = n3;
    n2->anterior = n1;
    n3->anterior = n2;

    cout << "Lista: ";
    lista.imprimir();

    return 0;
}
