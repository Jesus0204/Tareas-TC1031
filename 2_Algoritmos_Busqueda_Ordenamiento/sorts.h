/*
 * sorts.h
 *
 *  Created on: 07/09/2023
 *      Author: Jesús Alejandro Cedillo Zertuche 
 *      A01705442
 */

#ifndef SORTS_H_
#define SORTS_H_

// Creas la clase con todas las funciones y que sea un template
template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	int busqBinaria_aux(const std::vector<T>&, int low, int high, int val);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int low, int high);
	void store_temp(std::vector<T>&, std::vector<T>&, int low, int high);
	void juntar_array(std::vector<T>&, std::vector<T>&, int low, int mid, int high);
public:
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> ordenaBurbuja(std::vector<T>&);
	std::vector<T> ordenaMerge(std::vector<T>&);
    int busqSecuencial(const std::vector<T>&, int val);
	int busqBinaria(const std::vector<T>&, int val);

};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &sort_array){
	// Buscas el elemento más chico del arreglo, y al final haces el swap del primer elemento
	// no ordenado
	int min;

	// Recorres todo el arreglo que no está ordenado
	for (int i = 0; i < sort_array.size(); i++){
		min = i;
		// Empiezas a buscar el num más chico que no está ordenado y guardas la variable
		for (int j = i; j < sort_array.size(); j++){
			if (sort_array[min] > sort_array[j]){
				min = j;
			}
		}
		// Ya que encontró el elemento más chico no ordenado haces el swap
		swap(sort_array, i, min);
	}
	return sort_array;
}

template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T> &sort_array){
	// Va haciendo el swap hasta que el número está ordenado
	// Por lo mismo el primer ciclo va del último elemento hasta 0
	// Empieza en size - 1 porque es el último elemento del arreglo
	for (int i = sort_array.size() - 1; i > 0; i--){
		// Empiezas desde 0 hasta el elemento que no está ordenado (i)
		for (int j = 0; j < i; j++){
			// Si el elemento de la j es más grande que el que sigue haces el swap
			if (sort_array[j] > sort_array[j + 1]){
				swap(sort_array, j + 1, j);
			}
		}
	}

	return sort_array;
}

template <class T>
void Sorts<T>::store_temp(std::vector<T> &sort_array, std::vector<T> &temp, int low, int high){
	// Se copia el arreglo temporal al arreglo que se va a regresar
	for (int i = low; i <= high; i++){
		sort_array[i] = temp[i];
	}
}

template <class T>
void Sorts<T>::juntar_array(std::vector<T> &sort_array, std::vector<T> &temp, int low, int mid, int high){
	// Crear a las variables 
	int count_low, count_mid, count_temp_array;

	// El contador low empieza en el más bajo y acaba en la mitad, mientras que el mid acaba en high
	count_low = low;
	// Es en mid + 1 porque el contador de low acaba en mid
	count_mid = mid + 1;
	count_temp_array = low;

	// Recorres dos mitades del arreglo a la vez y hace comparaciones
	while (count_low <= mid && count_mid <= high){
		// Cuando el número que está más adelante es más grande, poner el del principio primero 
		if (sort_array[count_low] < sort_array[count_mid]){
			temp[count_temp_array] = sort_array[count_low];
			count_low++;
		}
		// Si el número de delante es más chico, ponerlo primero en la nueva lista
		else {
			temp[count_temp_array] = sort_array[count_mid];
			count_mid++;
		}
		// Incrementas el contador del arreglo temporal para guardar los datos adecuadamente
		count_temp_array++;
	}

	/* Lo de arriba acomoda algunos elementos (especialmente los de fuera de lugar)
	   Como todavía falta poner los elementos restantes, esto se hace de la siguiente forma: 
	*/

	/* Si el contador de low llego a mid, entonces llena los elementos de donde se quedo el contador de
	mid hasta que llegue a high
	*/
	if (count_low > mid) {
		for (; count_mid <= high; count_mid++) {
			temp[count_temp_array++] = sort_array[count_mid];
		}
	} 
	// Aquí pasa lo opuesto, donde se llenan los elementos antes de mid de donde se quedo el contador de low a mid
	else {
		for (; count_low <= mid; count_low++) {
			temp[count_temp_array++] = sort_array[count_low];
		}
	}
}


template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &sort_array, std::vector<T> &temp, int low, int high){
	// Declaras la variable del mid
	int mid;

	// Caso base que no regresa nada. El ordenamiento es en la copia del arreglo
	if ((high - low) == 0){
		return ;
	}
	// Cálculo de mid
	mid = (low + high) / 2;
	// Se divide el arreglo y solo se pasa la mitad a la función recursiva
	mergeSplit(sort_array, temp, low, mid);
	// Ahora se pasa la otra mitad hasta que también sea caso base
	mergeSplit(sort_array, temp, mid + 1, high);

	/* Esta parte del código no pasa hasta que la recursión acabe.  
	   O sea que empieza mientras el árbol de recursión va regresando y junta el arreglo ordenado
	*/

	// Llamas a mandar la función que ordena el arreglo y lo guarda en la temporal
	juntar_array(sort_array, temp, low, mid, high);
	// Ahora se pasa al arreglo temporal ordenado al original para sobreescrbirlo
	store_temp(sort_array, temp, low, high);

}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &sort_array){
	// Creas el arreglo temporal para que no se haga bolas con la recursión
	std::vector<T> temp(sort_array.size());

	// Llamas a la función auxiliar (recursiva)
	mergeSplit(sort_array, temp, 0, sort_array.size() - 1);

	return sort_array;
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &busq_array, int val){

	// La busqueda en donde se recorre cada elemento hasta encontrarlo
	for (int i = 0; i < busq_array.size(); i++){
		if (busq_array[i] == val){
			return i;
		}
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria_aux(const std::vector<T> &busq_array, int low, int high, int val){
	// Crear el valor del mid para partir el arreglo a la mitad
	int mid;

	if (low < high){
		// Definir el mid nuevo
		mid = (low + high) / 2;
		// Caso base
		if (busq_array[mid] == val){
			return mid;
		}
		// Si el valor del medio es más grande del que se busca, se corta a la mitad de la izquierda
		else if (busq_array[mid] > val) {
			return busqBinaria_aux(busq_array, low, mid, val);
		}
		// Ahora si el valor es más grande se busca en la segunda mitad
		else if (busq_array[mid] < val) {
			return busqBinaria_aux(busq_array, mid + 1, high, val);
		}
	}
	return -1;
}

// La función que llama a la otra función para que se pueda usar recursión
template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &original, int val){
	return busqBinaria_aux(original, 0, original.size() - 1, val);
}


#endif /* SORTS_H_ */