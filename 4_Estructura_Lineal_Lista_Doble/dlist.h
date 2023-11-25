/*
 * dlist.h
 *
 *  Created on: 28/09/2023
 *      Author: Jesús Alejandro Cedillo Zertuche 
 *      A01705442
 */
#ifndef DLIST_H_
#define DLIST_H_

// Declaras que hay una clase DList para que no de errores por el friend
template <class T> class DList;

template <class T>
class DLink {
    private:
        // El constructor con el valor
        DLink(T);

        // Los atributos donde value es tipo T, next es apuntador al Link que sigue y previous al anterior
        T value;
        DLink<T> *previous;
        DLink<T> *next;

        // Como son amigos, tienen acceso a cosas privadas de DLink
        friend class DList<T>;
};

// Constructor de la clase DLink con un solo valor (con el next hacia NULL y previous igual)
template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
class DList {
    public:
        // Agregas el constructor y destructor
	    DList();
	    ~DList();

        // Métodos pedidos
        void insertion (T val);
		int search (T val) const;
        void update (int pos, T val);
        T deleteAt(int pos);

        // Métodos auxiliares
		T deleteFirst();
		T deleteLast();
        std::string toStringForward() const;
        std::string toStringBackward() const;
        void clear();

    private:
        // El apuntador del primer node
        DLink<T> *head;
        // El apuntador del último node
        DLink<T> *tail;
        int 	 size;
};

// Constructor de DList
template <class T>
DList<T>::DList() : head(0), tail(0), size(0){}

// Destructor de DList
template <class T>
DList<T>::~DList() {
	clear();
}

// Aquí igual asumo que solo se puede agregar al final, de acuerdo a lo que pide el main
template <class T>
void DList<T>::insertion(T val){
	// Apuntador vacío de tipo DLink
	DLink<T> *newElement;
	// Creas en el heap el nuevo elemento
	newElement = new DLink<T> (val);

	// Para agregar se agrega diferente cuando el primer elemento que los demas
	if (size == 0){
		// Aseguras que el next del elemento sea un apuntador vacío
		newElement -> next = 0;
		// Aseguras que el previous del elemento sea un apuntador vacío
		newElement -> previous = 0;
		// Haces que el head (lo que inicia la lista) sea el apuntador que acabas de crear
		head = newElement;
		// Igual haces que el tail sea el elemento que hay
		tail = newElement;
	} 
	// Todos los otros casos se agregan al final de la lista
	else {
		// Haces que el next del actual último elemento sea igual al que se va a insertar
		tail -> next = newElement;
		// Haces que el previous del nuevo elemento sea igual al que estaba antes
		newElement -> previous = tail;
		// Aseguras que el next del nuevo elemento sea igual a Null
		newElement -> next = 0;
		// Cambias el tail por el nuevo elemento en la lista
		tail = newElement;
	}
	// Incrementas el size
		size++;
}

template <class T>
int DList<T>::search(T val) const {
	// Creas el apuntador de tipo Dlink que va a recorrer el arreglo
	DLink<T> *p;
	// Haces una variable que va a contar las posiciones en la la lista
	int count = 0;

	/* Aquí es importante mencionar que se puede comenzar de tail, pero como no se sabe si la
	   lista está ordenada, no se puede asegurar que hacerlo de atrás para adelante sea más rápido
	   Para las otras funciones se puede usar por la posición y size
	*/ 

	// Haces que p empiece en el primer elemento
	p = head;
	// Haces que el while recorra todo la lista hasta el último elemento
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

// Aquí se tiene la posición, por lo que se puede decidir si se empieza en head o tail 
// Dependiendo del size
template <class T>
void DList<T>::update(int pos, T val){
	// Sacar la mitad para decidir si se recorre desde el head o tail
	int middle = ((size - 1) / 2);
	// Inicializas la variable
	int count;

	// Creas el apuntador de tipo Dlink que va a recorrer el arreglo
	DLink<T> *p;

	// Dependiendo de middle aquí del principio a la mitad
	if (pos <= middle){
		// Empieza en el principio de la lista
		p = head;
		// Count empieza con el primer indice de la lista
		count = 0;
		// Haces que el while recorra toda la lista desde el principio hasta la mitad
		while (p != 0){
			// Si el lugar indicado es igual a la posición que se pide cambiar
			if (pos == count){
				// Como ya está en el lugar correcto, cambias el valor al que apunta p
				p -> value = val;
			}
			// Si no es haces que el apuntador se mueva al siguiente elemento
			p = p -> next;
			// Como no les igual a la posición
			count++;
		}
	}
	// La otra mitad de la lista
	else if (pos > middle){
		// Empieza al final de la lista
		p = tail;
		// Empiezas en la último índice de la lista
		count = size - 1;
		// Haces que el while recorra toda la lista desde el final hasta la mitad
		while (p != 0){
			// Si el lugar indicado es igual a la posición que se pide cambiar
			if (pos == count){
				// Como ya está en el lugar correcto, cambias el valor al que apunta p
				p -> value = val;
			}
			// Si no es haces que el apuntador se mueva al elemento anterior
			p = p -> previous;
			// Como no les igual a la posición
			count--;
		}
	}
}

// Igual para salvar tiempo se usa la mitad
template <class T>
T DList<T>::deleteAt(int pos){
	// Sacar la mitad para decidir si se recorre desde el head o tail
	int middle = ((size - 1) / 2);
	// Inicializas la variable
	int count;
	// Creas la variable que se va a regresar
	T val;

	// Creas el apuntador de tipo Dlink que va a recorrer el arreglo
	DLink<T> *elemento_borrar;

	// Dependiendo de middle aquí del principio a la mitad
	if (pos <= middle){
		// Para el primer elemento que es diferente
		if (pos == 0){
			val = deleteFirst();
			// Regresar el valor para que se salga de la función
			return val;
		}
		// Empiezas al principio de la lista
		elemento_borrar = head;
		// Empiezas en el segundo elemento, ya que el primero esta cubierto
		count = 1;
		elemento_borrar = elemento_borrar -> next;
		// Recorres toda la lista hasta la mitad
		while (elemento_borrar != 0){
			// Si se llega al elemento a borrar
			if (pos == count){
				// Cambias el previous del siguiente elemento a borrar al elemento que esta antes de borrar
				elemento_borrar -> next -> previous = elemento_borrar -> previous;
				// Cambias el next del elemento anterior a borrar al elemento que está después de bprrar
				elemento_borrar -> previous -> next = elemento_borrar -> next;
				// Guardas la variable del elemento a borrar
				val = elemento_borrar -> value;
				// Borrar el elemento
				delete elemento_borrar;
				// Quitarle uno al size
				size--;
				// Regresar el valor
				return val;
			}
			// Si no es haces que el apuntador se mueva al siguiente elemento
			elemento_borrar = elemento_borrar -> next;
			// Aumentar el contador
			count++;
		}
	}
	// La otra mitad de la lista
	else if (pos > middle){
		// Para el último elemento que también cambia de los demás
		if (pos == (size - 1)){
			val = deleteLast();
			// Regresar el valor para que se salga de la función
			return val;
		}
		// Empiezas al final de la lista
		elemento_borrar = tail;
		// Empiezas en el último indice
		count = size - 1;
		elemento_borrar = elemento_borrar -> previous;
		// Recorres toda la lista hasta la mitad (de atrás para adelante)
		while (elemento_borrar != 0){
			// Si se llega al elemento a borrar
			if (pos == count){
				// Cambias el previous del siguiente elemento a borrar al elemento que esta antes de borrar
				elemento_borrar -> next -> previous = elemento_borrar -> previous;
				// Cambias el next del elemento anterior a borrar al elemento que está después de bprrar
				elemento_borrar -> previous -> next = elemento_borrar -> next;
				// Guardas la variable del elemento a borrar
				val = elemento_borrar -> value;
				// Borrar el elemento
				delete elemento_borrar;
				// Quitarle uno al size
				size--;
				// Regresar el valor
				return val;
			}
			// Si no es haces que el apuntador se mueva al elemento anterior
			elemento_borrar = elemento_borrar -> previous;
			// Decrementar ya que vamos hacia atrás
			count--;
		}
	}
	// Para quitar el warning
	return -1;
}

// Haces la función separada para facilitar el deleteAt.
template <class T>
T DList<T>::deleteFirst(){
	// Creas el apuntador de tipo link
	DLink<T> *p;
	// Creas la variable que se va a regresar
	T val;

	// Asegurar para listas de un solo elemento
	if (head == tail){
		head = 0;
		tail = 0;
	}

	// Empieza en el primer elemento
	p = head;
	// Guardas el valor
	val = p -> value;
	// Cambias el valor del head al siguiente elemento
	head = p -> next;
	// Haces que el previous del siguiente elemento ante de borrarlo sea Null
	p -> next -> previous = 0;
	// Le quitas uno a size
	size--;

	// Borras el elemento ya que nada apunta hacia él
	delete p;
	// Regresas el valor
	return val;
}

// Haces la función separada para facilitar el deleteAt.
template <class T>
T DList<T>::deleteLast(){
	// Creas el apuntador de tipo link
	DLink<T> *p;
	// Creas la variable que se va a regresar
	T val;

	// Empieza en el primer elemento
	p = tail;
	// Guardas el valor
	val = p -> value;
	// Cambias el valor del tail al elemento anterior
	tail = p -> previous;
	// Haces que el next del elemento anterior sea igual a 0
	p -> previous -> next = 0;
	// Le quitas uno a size
	size--;

	// Borras el elemento ya que nada apunta hacia él
	delete p;
	// Regresas el valor
	return val;
}

// Funciones de tostring para el main
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

// La función que borra todo que es llamada por el destructor
template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

    // Haces que p empiece en head
	p = head;
    // Recorres toda la lista borrando todo hasta el final
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
    // Haces NULL los últimos apuntadores y el size 0
	head = 0;
	tail = 0;
	size = 0;
}

#endif /* DLIST_H_ */