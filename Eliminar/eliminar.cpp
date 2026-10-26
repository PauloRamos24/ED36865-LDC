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

    void eliminar(int dato)
    {
        if (cabeza == nullptr)
        {
            cout << "Lista vacia." << endl;
            return;
        }

        Nodo<int>* actual = cabeza;

        do
        {
            if (actual->getDato() == dato)
            {
                break;
            }

            actual = actual->getSiguiente();

        } while (actual != cabeza);

        if (actual->getDato() != dato)
        {
            cout << "Elemento no encontrado." << endl;
            return;
        }

        if (actual->getSiguiente() == actual)
        {
            delete actual;
            cabeza = nullptr;
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
            cout << actual->getDato() << " ";
            actual = actual->getSiguiente();

        } while (actual != cabeza);

        cout << endl;
    }
};

int main()
{
    ListaDobleCircular lista;

    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);

    cout << "Lista inicial:" << endl;
    lista.imprimir();

    cout << "Eliminando 20..." << endl;
    lista.eliminar(20);

    cout << "Lista despues de eliminar:" << endl;
    lista.imprimir();

    return 0;
}