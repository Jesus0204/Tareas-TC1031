/*
 * quadratic.h
 *
 *  Created on: 16/11/2023
 *      Author: Jesús Alejandro Cedillo Zertuche
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
    // El apuntador de la función y el tamaño y elementos actuales
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

    // Los arreglos y el valor inicial
	Key *keys;
	Key initialValue;
	Value *values;

    // Función auxiliar que saca el indice de cierta llave
	long indexOf(const Key) const;

public:
    // Constructor y destructor
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
	~Quadratic();

    // Funciones pedidas a implementar
    void put(Key, Value);
    Value get(const Key);

    // Funciones auxiliares del programa
	string toString() const;
};

template <class Key, class Value>
Quadratic <Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	// Inicializas variables en la clase
	size = sze;
	initialValue = init;
	count = 0;
	// Creas la lista de Keys en el heap
	keys = new Key[size];
	// Asignar el valor inicial de la llave al arreglo dinámico
	for (int i = 0; i < size; i++){
		keys[i] = initialValue;
	}

	// Creas la lista de valores dinamica
	values = new Value[size];
	// Asignar el valor inicial de cada valor al arreglo dinámico
	for (int i = 0; i < size; i++){
		values[i] = 0;
	}

	// Asignas la función de hash del main a la función de la clase
	func = f;
}

template <class Key, class Value>
Quadratic <Key, Value>::~Quadratic() {
	// Borras los arreglos dinámicos
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	// Las demás funciones les pones como 0
	size = 0;
	func = 0;
	count = 0;
}

template <class Key, class Value>
long Quadratic <Key, Value>::indexOf(const Key k) const {
	// Creas las variables de inicio, y la que itera
	unsigned int i, start;

	// Sacas el indice con el cual empezar de acuerdo al hash y aseguras que sea un indice con el %
	start = i = func(k) % size;
	// Crear el contador para aplicar el quadratic
	int count_hash = 1;
	do {
		// Si el valor de keys es igual al input regresarlo
		if (keys[i] == k) {
			return i;
		}
		// Pasar al siguiente indice de acuerdo al quadratic hash
		i = ((count_hash * count_hash) + i) % size;
		count_hash++;
 	} 
	// Repetir hasta que start e i sean iguales
	while (start != i);
	// Si no encontro nada regresar un menos 1 que no encontro nada
	return -1;
}

template <class Key, class Value>
void Quadratic <Key, Value> :: put(Key k, Value v){
	// Crear las variables
	unsigned int i, start;
	long pos;

	// Si el key ya tiene algo, actualizas ese key con el nuevo valor
	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return;
	}

	// Sacas el lugar con el hash donde se va a insertar
	start = i = func(k) % size;
	// Crear el contador para aplicar el quadratic
	int count_hash = 1;
	do {	
		// Si ese indice esta vacio (tiene el initial value)
		if (keys[i] == initialValue) {
			// Pones la llave y el valor e aumentas el count
			keys[i] = k;
			values[i] = v;
			count++;
			return;
		}
		// Pasar al siguiente indice de acuerdo al quadratic hash
		i = ((count_hash * count_hash) + i) % size;
		count_hash++;
	} 
	// Todo mientras i no sea igual a start
	while (start != i);
}

template <class Key, class Value>
Value Quadratic <Key, Value> :: get(const Key k){
	// Buscar el indice de la llave con la función
	long pos = indexOf(k);
	// Si la posición si existe
	if (pos != -1) {
		// Regresar el valor con esa posición
		return values[pos];
	}
}

// Impresion clase quadratic
template <class Key, class Value>
string Quadratic <Key, Value>::toString() const {
    stringstream aux;
    for (int i = 0; i < size; i++){
    		if (keys[i] != initialValue){
    			aux << "(" << i << " ";
    			aux << keys[i] << " : " << values[i] << ") ";
    		}
    }
    return aux.str();
}

#endif /* QUADRATIC_H_ */