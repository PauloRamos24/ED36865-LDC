#include <iostream>
using namespace std;

template <typename T>
class Nodo
{
private:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

public:
    Nodo(T dato)
    {
        this->dato = dato;
        siguiente = nullptr;
        anterior = nullptr;
    }

    T getDato()
    {
        return dato;
    }

    void setDato(T dato)
    {
        this->dato = dato;
    }

    Nodo<T>* getSiguiente()
    {
        return siguiente;
    }

    void setSiguiente(Nodo<T>* siguiente)
    {
        this->siguiente = siguiente;
    }

    Nodo<T>* getAnterior()
    {
        return anterior;
    }

    void setAnterior(Nodo<T>* anterior)
    {
        this->anterior = anterior;
    }
};

class ListaDobleCircular
{
private:
    Nodo<int>* cabeza;

public:

    ListaDobleCircular()
    {
        cabeza = nullptr;
    }

    void insertar(int dato)
    {
        Nodo<int>* nuevo = new Nodo<int>(dato);

        if (cabeza == nullptr)
        {
            cabeza = nuevo;
            cabeza->setSiguiente(cabeza);
            cabeza->setAnterior(cabeza);
        }
        else
        {
            Nodo<int>* cola = cabeza->getAnterior();

            nuevo->setSiguiente(cabeza);
            nuevo->setAnterior(cola);

            cola->setSiguiente(nuevo);
            cabeza->setAnterior(nuevo);
        }
    }

    void imprimir()
    {
        if (cabeza == nullptr)
        {
            cout << "Lista vacia." << endl;
            return;
        }

        Nodo<int>* actual = cabeza;

        do
        {
            cout << "[" << actual->getDato() << "]";

            actual = actual->getSiguiente();

            if (actual != cabeza)
            {
                cout << " <-> ";
            }

        } while (actual != cabeza);

        cout << " <-> vuelve al inicio" << endl;
    }
};

int main()
{
    ListaDobleCircular lista;

    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);

    cout << "Lista doble circular:" << endl;

    lista.imprimir();

    return 0;
}