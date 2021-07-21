#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <cstddef>


template <class T>
struct nodo {
    T instancia;
    nodo<T>* sgte;
};

template <class T>
class Lista {
    public :
        Lista(T);
        Lista();
        ~Lista();
        void add_nodo(T);
        void set_cabeza(T);
        nodo<T>* get_cabeza();
        nodo<T>* get_cola();
        bool esta_vacia();
    private:
        std::size_t size;
        nodo<T>* cabeza;
        nodo<T>* cola;
};

template <class T>
Lista<T>::Lista() {
    
    this -> size = 0;
    this -> cabeza = this -> cola = NULL;
}

template <class T>
Lista<T>::Lista(T instancia) {
    this -> cabeza = new nodo<T>;
    this -> cabeza -> instancia = instancia;
    this -> cabeza -> sgte = NULL;
    this -> cola = cabeza;
    this -> size = 1;
}

template <class T>
Lista<T>::~Lista() {
    
    // Destructor que libera nodo a nodo la lista de forma genérica: while (...) { free ... }
}

template <class T>
void Lista<T>::add_nodo(T instancia) {
    nodo<T>* q = new nodo<T>;
    q -> instancia = instancia;
    q -> sgte = NULL;
    if (this -> cabeza == NULL) {
        this -> cabeza = q;
        this -> cola = q;
    } else {
        cola -> sgte = q;
        cola = q;
    }
    ++ this -> size;
}

template <class T>
nodo<T>* Lista<T>::get_cabeza() {
    return this -> cabeza;
}

template <class T>
nodo<T>* Lista<T>::get_cola() {
    return this -> cola;
}

template <class T>
bool Lista<T>::esta_vacia() {
    if (this -> cabeza == NULL)
        return true;
    else
        return false;
}

#endif