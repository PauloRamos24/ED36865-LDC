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
    void setCabeza(Nodo<int>* nodo)
    {
        cabeza = nodo;
    }
};
int main()
{
    ListaDobleCircular lista;
    Nodo<int>* n1 = new Nodo<int>(10);
    Nodo<int>* n2 = new Nodo<int>(20);
    n1->setSiguiente(n2);
    n2->setSiguiente(n1);
    n1->setAnterior(n2);
    n2->setAnterior(n1);
    lista.setCabeza(n1);
    cout << "Lista inicial:" << endl;
    lista.imprimir();
    cout << "Eliminando 20..." << endl;
    lista.eliminar(20);
    cout << "Lista despues de eliminar:" << endl;
    lista.imprimir();
    return 0;
}