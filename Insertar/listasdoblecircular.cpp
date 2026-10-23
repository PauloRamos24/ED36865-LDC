#include <iostream>
using namespace std;


template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T valor) {
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
    }
};


template <typename T>
class ListaDobleCircular {
private:
    Nodo<T>* cabeza;
    int tamanio;

public:
    ListaDobleCircular() {
        cabeza = nullptr;
        tamanio = 0;
    }

   

    bool estaVacia() {
        return cabeza == nullptr;
    }

    int getTamanio() {
        return tamanio;
    }

    
    void insertarAlFinal(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        if (estaVacia()) {
        
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
            cabeza = nuevo;
        } else {
            Nodo<T>* ultimo = cabeza->anterior;

            nuevo->siguiente = cabeza;
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            cabeza->anterior = nuevo;
        }
        tamanio++;
    }

   
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
        cabeza = nuevo;   // el nuevo nodo pasa a ser la cabeza
        tamanio++;
    }

   

   
    
};


int main() {
    ListaDobleCircular<int> lista;

    lista.insertarAlFinal(10);
    lista.insertarAlFinal(20);
    lista.insertarAlFinal(30);
    lista.insertarAlInicio(5);
    

   
    cout << "Tamano: " << lista.getTamanio() << endl;

    return 0;
}



