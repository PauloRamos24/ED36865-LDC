/***********************************************************************
 * Module:  Nodo.h
 * Author:  IdeaPad Gaming
 * Modified: viernes, 23 de octubre de 2026 9:51:05
 * Purpose: Declaration of the class Nodo
 ***********************************************************************/

#if !defined(__ListasDoblesEliminar_Nodo_h)
#define __ListasDoblesEliminar_Nodo_h

class Nodo
{
public:
int dato;
   Nodo* siguiente;
   Nodo* anterior;

   Nodo(int val);
   
protected:
private:


};

#endif