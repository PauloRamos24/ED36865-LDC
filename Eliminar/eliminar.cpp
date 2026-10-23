
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

    void eliminar(int dato) {
        if (cabeza == nullptr) {
            cout << "La lista esta vacia" << endl;
            return;
        }

        Nodo* actual = cabeza;

        do {
            if (actual->dato == dato) {

                // Caso 1: solo existe un nodo
                if (actual->siguiente == actual) {
                    cabeza = nullptr;
                } else {
                    // Enlazar el anterior con el siguiente
                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;

                    // Si se elimina la cabeza
                    if (actual == cabeza) {
                        cabeza = actual->siguiente;
                    }
                }

                delete actual;
                cout << "Elemento eliminado" << endl;
                return;
            }

            actual = actual->siguiente;

        } while (actual != cabeza);

        cout << "Elemento no encontrado" << endl;
    }

    void imprimir() {
        if (cabeza == nullptr) {
            cout << "La lista esta vacia" << endl;
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

    cout << "Lista original: ";
    lista.imprimir();

    int valor = 20;
    lista.eliminar(valor);

    cout << "Lista despues de eliminar: ";
    lista.imprimir();

    return 0;
}
