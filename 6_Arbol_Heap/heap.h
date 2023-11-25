/*
 * heap.h
 *
 *  Created on: 30/10/2023
 *      Author: Jesús Alejandro Cedillo Zertuche
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>

using namespace std;

template <class T>
class Heap {
    private: 
        // Atributos del árbol
        T *data;
        unsigned int tamano;
        unsigned int count;

        // Funciones auxiliares privadas
        unsigned int parent(unsigned int pos) const;
        unsigned int left(unsigned int pos) const;
        unsigned int right(unsigned int pos) const;
        void heapify(unsigned int pos);
        void swap(unsigned int, unsigned int);

    public: 
        // Constructor y destructores
        Heap(unsigned int sze);
        ~Heap();

        // Funciones a implementar 
        void push(T val);
        void pop();
        T top();
        bool empty() const;
        unsigned int size();

        // Funciones auxiliares
        string toString() const;
};

template <class T>
unsigned int Heap<T> :: parent(unsigned int pos) const{
    /* Según la aritmética del árbol, para encontrar al padre se divide entre dos
     * Porque entre más abajo más grande el valor de la posición
     * Como C++ redondea para abajo jala para cualquiera
     */
    return pos / 2;
}

template <class T>
unsigned int Heap<T> :: left(unsigned int pos) const{
    /* Según la aritmética del árbol, para encontrar al hijo left solo se múltiplica por 2
     * Porque entre más abajo más grande el valor de la posición
     * Aparte como todos los hijos left son pares no se hace nada más
     */
    return pos * 2;
}

template <class T>
unsigned int Heap<T> :: right(unsigned int pos) const{
    /* Según la aritmética del árbol, para encontrar al hijo right solo se múltiplica por 2 + 1
     * Porque entre más abajo más grande el valor de la posición
     * Aparte como todos los hijos right tienen número impar por eso el + 1
     */
    return (pos * 2) + 1;
}

// El swap que hemos usado toda la vida
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	// La función swap que siempre se ha usado
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T> :: heapify(unsigned int pos){
    // Sacas el hijo left del nodo con la aritmética del árbol
    unsigned int le = left(pos);
    // Sacas el hijo right del nodo con la aritmética del árbol
    unsigned int ri = right(pos);
    // Haces que el índice con el mínimo sea la posición donde se llamo el heapify
    unsigned int min = pos;

    // Aseguras que el índice exista en el arreglo
    if (le <= count)
        // Si el hijo left de pos es más chico que min
        if (data[le] < data[min])
            // El nuevo mínimo es el índice de ese hijo left
            min = le;
    // Aseguras que el índice exista en el arreglo
    if (ri <= count)
        // Si el hijo right de pos es más chico que min
        if (data[ri] < data[min])
            // El nuevo mínimo es el índice de ese hijo right
            min = ri;

    // Si el min cambio por alguna de los ifs anteriores, entonces llamar recursivamente la función
    if (min != pos) {
		// Cambias la posición actual y el mínimo encontrado
		swap(pos, min);
		// Llamas la función recursivamente
		heapify(min);
	}
}

template <class T>
Heap<T> :: Heap(unsigned int sze){
    // Haces que size de heap sea igual al tamaño indicado
	tamano = sze + 1;
	// Creas el arreglo dinamico
	data = new T[tamano];
	// Haces count = 1 porque no hay elementos
	count = 1;
}

template <class T>
Heap<T> :: ~Heap() {
	// Borras el arreglo dinámico
	delete [] data;
	// Haces que data sea igual a null
	data = 0;
	// Reseteas size y count a 0
	count = 0;
	tamano = 0;
}

// La función que agrega al final del árbol y reordena a ese elemento y padres para que la prioridad se respete
template <class T>
void Heap<T> :: push(T val){
    // Creas la variable temporal
    unsigned int pos;

    // Haces que pos sea el lugar inicial donde se va a agregar
    pos = count;
    // Agregas uno a count, porque ya tienes otro elemento
    count++;

    /* Mientras este en un lugar legal del arreglo (que pos siga siendo positivo) y
	 * Si el valor del papá es más grande que el del hijo */
	while (pos > 0 && val < data[parent(pos)]) {
		/* Aquí en la primera iteración pos es igual al último lugar de la lista
         * Como el valor a agregar tiene más prioridad, haces que el data de pos
         * sea igual al de papá (es como un swap). 
         * Después se cambia pos al índice de su papá y se itera de nuevo 
         * (repite hasta que se cumplan condiciones). 
         * Si el valor no tiene prioridad entonces se tiene la posición donde se tiene que agregar
         */

		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}

    /* Al final que encontró la posición donde el padre es más chico (tiene más prioridad), 
     * insertas el valor en esa posición. Si no entró al ciclo, entonces es al final del árbol. 
     */
	data[pos] = val;
}

// La función que borra la raíz y reacomoda el árbol
template <class T>
void Heap<T> :: pop(){
    // Haces que el nuevo elemento raíz, sea el último que se encuentra en el árbol
	data[1] = data[--count];
    // Llamas el heapify para que se reoordene el árbol y se encuentre el elemento con más prioridad
    heapify(1);
}

// La función que saca el elemento que está en la raíz
template <class T>
T Heap<T> :: top(){
    // Si está vacía regresar un -1 indicando que no tiene elementos
    if (empty())
        return -1;
    
    // Sacas el elemento que está en el root y lo regresas
    T top_value = data[1];
    return top_value;
}

// La función que verifica si el árbol está vacío
template <class T>
bool Heap<T>::empty() const {
	// Si count es igual a 1 no se han insertado elementos entonces está vacío
	if (count == 1)
		return true;
	else 
        return false;
}

// La función que regresa cuantos elementos tiene la lista
template <class T>
unsigned int Heap<T> :: size(){
    /* Regresas el atributo donde está guardado la cantidad de datos del heap 
     (-1 porque el count está en el siguiente que se puede agregar) */
    return count - 1;
}

template <class T>
string Heap<T> :: toString() const {
	std::stringstream aux;
	aux << "[";	
    for (unsigned int i = 1; i < count; i++) {
		if (i != 1) {
			aux << " ";
		} 
        aux << data[i];
	} 
    aux << "]";
	return aux.str();
}

#endif /* HEAP_H_ */