/*
 * list.h
 *
 *  Created on: 25/09/2023
 *      Author: Jesús Alejandro Cedillo Zertuche 
 *      A01705442
 */
#ifndef LIST_H_
#define LIST_H_

using namespace std;

// Declaras que hay una clase List para que no de errores por el friend
template <class T> class List;

template <class T>
class Link {
	private:
		// El constructor con el valor
		Link(T);

		// Los atributos donde value es tipo T y next es apuntador al Link que sigue
		T value;
		Link<T>* next;

		// Como son amigos, tienen acceso a cosas privadas de Link
		friend class List<T>;
};

// Constructor de la clase link con un solo valor (con el next hacia NULL)
template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
class List {
    public:
		// Agregras el constructor
		List();

		// Métodos pedidos
        void insertion (T val);
		int search (T val) const;
        void update (int pos, T val);
        T deleteAt(int pos);
        std::string toString() const;
		T deleteFirst();

    private:
        // El apuntador del primer node
        Link<T> *head;
        int 	size;
};

// Constructor de List
template <class T>
List<T>::List() : head(0), size(0){}

// De acuerdo a las especificaciones del main, voy a asumir que solo se puede agregar al final de la lista
// En el main solo viene que se agrega al principio la primera vez, por lo que no es necesario un método de add_First
// Es algo que considero que puede facilitar el diseño del programa y cumple con los requerimientos
template <class T>
void List<T>::insertion(T val){
	// Es diferente el primer elemento que los demás, por lo que se pone el if
	if (size == 0){
		// Apuntador vacío de tipo link
		Link<T> *newElement;
		// Creas en el heap el nuevo link con el valor dado
		newElement = new Link<T> (val);
		// Aseguras que el next del elemento sea un apuntador vacío
		newElement -> next = 0;
		// Haces que el head (lo que inicia la lista) sea el apuntador que acabas de crear
		head = newElement;
		// Incrementas el size
		size++;
	}
	else {
		// Apuntador vacío de tipo link para el elemento nuevo, al igual que el que itera la lista
		Link<T> *newElement, *p;
		// Creas en el heap el nuevo link con el valor dado
		newElement = new Link<T> (val);
		
		// Haces que el apuntador que recorre la lista sea igual al head (primer elemento)
		p = head;
		// Recorres la lista hasta llegar a un apuntador vacío (next)
		while (p -> next != 0){
			p = p -> next;
		}
		// Como se agrega al final, el siguiente elemento es vacío
		newElement -> next = 0;
		// Haces que el next del último elemento (que se encontró en el while) apunte al nuevo elemento
		p -> next = newElement;
		// Incrementas el tamaño
		size++;
	}
    
}

template <class T>
int List<T>::search(T val) const {
	// Creas el apuntador de tipo link que va a recorrer el arreglo
	Link<T> *p;
	// Haces una variable que va a contar las posiciones en la la lista
	int count = 0;

	// Haces que p empiece en el primer elemento
	p = head;
	// Haces que el while recorra todo la lista hasta el último elemento
	// Aquí es sin el next, porque si no nunca se entra al ciclo a hacer la comparación
	while (p != 0){
		// Si el valor que apunta p es igual al valor regresar el contador
		if (p -> value == val){
			return count;
		}
		// Si no es haces que el apuntador se mueva al siguiente elemento
		p = p -> next;
		// Como no lo encontró aumentas uno el contador de índices
		count++;
	}
	// Si no lo encontró regresar un -1
	return -1;
}

template <class T>
void List<T>::update(int pos, T val){
	// Creas el apuntador de tipo link que va a recorrer el arreglo
	Link<T> *p;
	// Haces una variable que va a contar las posiciones en la la lista
	int count = 0;

	// Haces que p empiece en el primer elemento
	p = head;
	// Haces que el while recorra todo la lista hasta el último elemento
	while (p != 0){
		// Si el lugar indicado es igual a la posición que se pide cambiar
		if (count == pos){
			// Como ya está en el lugar correcto, cambias el valor al que apunta p
			p -> value = val;
		}
		// Si no es haces que el apuntador se mueva al siguiente elemento
		p = p -> next;
		// Como no les igual a la posición
		count++;
	}
}

template <class T>
T List<T>::deleteAt(int pos){
	// Creas el apuntador de tipo link que va a recorrer el arreglo
	Link<T> *elemento_borrar, *elemento_antes;
	// Haces que count empiece en 1, porque la función del primer elemento no depende de count
	int count = 1;
	// Creas la variable que se va a regresar
	T val;

	// Haces que ambos apuntadores empiecen en el head
	elemento_borrar = head;
	elemento_antes = head;
	// Para borrar el primer elemento ya tiene una función, entonces se empieza desde el segundo elemento
	// El elemento antes ya empieza en el primer elemento
	elemento_borrar = elemento_borrar -> next;
	// Haces que el while recorra todo la lista hasta el último elemento
	while (elemento_borrar != 0){
		// Si es el primer elemento, se cambia el head y se borra
		if (pos == 0){
			val = deleteFirst();
			// Regresar el valor para que se salga de la función
			return val;
		}
		// Para borrar cualquier otro elemento encontrado en la lista
		else if (count == pos){
			// Para no perder lo que sigue en la lista, hay que modificar el next del elemento anterior
			elemento_antes -> next = elemento_borrar -> next;
			// Guardar la variable a regresar
			val = elemento_borrar -> value;
			// Borrar el elemento
			delete elemento_borrar;
			// Quitarle uno al size
			size--;
			// Regresar el valor
			return val;
		}
		// Si no es haces que el apuntador se mueva al siguiente elemento
		elemento_antes = elemento_antes -> next;
		elemento_borrar = elemento_borrar -> next;
		// Como no les igual a la posición
		count++;
	}
	// Para quitar el warning
	return -1;
}

// Haces la función separada para facilitar el deleteAt.
template <class T>
T List<T>::deleteFirst(){
	// Creas el apuntador de tipo link
	Link<T> *p;
	// Creas la variable que se va a regresar
	T val;

	// Haces que p empiece en el primer elemento
	p = head;
	// Como p apunta al primer elemento, hay que cambiar el head. Esto se hace con next
	head = p -> next;
	// Guardas el valor para regresarlo
	val = p -> value;
	// Le quitas uno a size
	size--;

	// Borras el elemento ya que nada apunta hacia él
	delete p;
	// Regresas el valor
	return val;
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
    // Creas el apuntador que recorre la lista
	Link<T> *p;

    // Apunta hacia el primer elemento
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
        // Saca cada elemento mientras el siguiente no sea NULL
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

#endif /* LIST_H_ */