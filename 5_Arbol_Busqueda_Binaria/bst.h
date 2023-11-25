/*
 * bst.h
 *
 *  Created on: 9/10/2023
 *      Author: Jesús Alejandro Cedillo Zertuche
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>

using namespace std;

// Header para el friend
template <class T> class BST;

/*
El nodo es el circulito.
Tiene el valor, y los apuntadores de sus hijos en la derecha y en la izquierda
*/ 
template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

public:
    // Constructor
	TreeNode(T);

    // Funciones simples implementadas en clase
    void add(T);
	bool find(T, int&);

    // Funciones auxiliares de funciones creadas
    int whatlevelamI(T val, int& count);
    int height(int& count, TreeNode<T>* root);
    void ancestors_exist(stringstream&, T val);
    void ancestors_recursion(stringstream &aux, T val);
    int count_elements(int& count);
    void print_level(stringstream &aux, TreeNode<T>* root, int level, int elements, int& element_num);

    // Funciones distintas para imprimir el árbol
    void preorder(stringstream&) const;
	void inorder(stringstream&) const;
    void postorder(stringstream&) const;
    void level_by_level(stringstream&, TreeNode<T>* root);

	friend class BST<T>;
};

// Creas el nodo donde insertar el valor
template <class T>
TreeNode<T>::TreeNode(T val): value(val), left(0), right(0) {}

// Función de agregar
template <class T>
void TreeNode<T>::add(T val) {
	// Comparas el valor a insertar contra el valor del nodo
	if (val < value){
		// Si no es nulo, se vuelve a llamar la función con recursión. 
		if (left != 0){
			// Aquí el left es el hijo, y se llama la función para que haga la comparación
			left -> add(val);
		}
		// Si es Nulo, ahí se agrega y crea el objeto
		else {
			left = new TreeNode<T>(val);
		}
	}
	// Si no, se inserta a la derecha y se hace lo mismo, donde se inserta hasta que llege a nulo
	else {
		if (right != 0){
			right -> add(val);
		}
		else {
			right = new TreeNode<T>(val);
		}
	}
}

// Función de buscar
template <class T>
bool TreeNode<T>::find(T val, int &count) {
	// El caso base donde si lo encontró
	if (val == value){
		return true;
	}
	// Si es menor recorre hacia la izquierda
	else if (val < value){
		// Si es nulo, llegó al final y no lo encontró
		if (left == 0){
			return false;
		}
		// Si no es nulo, vas a left y llamas a la recursión con ese nodo
		else {
            count++;
			return left -> find(val, count);
		}
	}
	// Si es mayor reocorre hacia la derecha
	else if (val > value){
		// Si es nulo, es caso base y no lo encontró
		if (right == 0){
			return false;
		}
		// Si no es nulo, vas al hijo de right y llamas a la recursión con ese nodo
		else {
            count++;
			return right -> find(val, count);
		}
	}
    // Regresar -1 que no lo encontró y para que no tenga warning
    else {
        return -1;
    }
}

template <class T>
int TreeNode<T>::whatlevelamI(T val, int& count){
    // Si en el find encuentra el valor regresar el counter
    if (find(val, count) == true){
        return count;
    }
    // Si no lo encontró entonces regresar -1 que no existe
    else {
        return -1;
    }
}

// Pasas el level donde se guarda, y el root, para que al revisar el nivel lo haga de la raíz
template <class T>
int TreeNode<T>::height(int& level, TreeNode<T>* root){
    // Creas variable para guardar
    int level_count;
    // Inicializas el count en 1
    int count = 1;
    
    // Si existe árbol en left
    if (left != 0){
        // Buscas el nivel de left y lo guardas
        level_count = root -> whatlevelamI(left -> value, count);
        // Como whatlevelamI usa paso por referencia, sobreescribes a 1 para siguiente nivel recursión
        count = 1;
        // Comparas el nivel a ver si es uno más alto. Si es lo guardas en level
        if (level_count > level){
            level = level_count;
        }
        // Llamas la recursión pasando al nodo de abajo y pasando la raíz
        left -> height(level, root);
    }
    // Si existe árbol en right
    if (right != 0){
        // Buscas el nivel de right y lo guardas
        level_count = root -> whatlevelamI(right -> value, count);
        // Como whatlevelamI usa paso por referencia, sobreescribes a 1
        count = 1;
        // Comparas el nivel a ver si es uno más alto. Si es lo guardas en level
        if (level_count > level){
            level = level_count;
        }
        // Llamas la recursión pasando al nodo de abajo y pasando la raíz
        right -> height(level, root);
    }

    // Después de que haya acabado regresas level
    return level;
}

template <class T>
void TreeNode<T>::ancestors_exist(stringstream &aux, T val){
    // Para poder usar el valor de find
    int count = 1;
    // Asegurar que el valor exista
    if (find(val, count) == true){
        ancestors_recursion(aux, val);
    }
}

template <class T>
void TreeNode<T>::ancestors_recursion(stringstream &aux, T val){

    // Caso base para que la recursión pare
    if (value == val){
        return;
    }
    // Guardas el al string
    aux << value;

    // Esta función toma como raíz el nodo, y ve en que nivel esta comparado con ese nodo
    int count_space = 1;
    whatlevelamI(val, count_space);

    /* Ahora, como no se esta imprimiendo el valor, si no sus ancestors
       cuando sea el último ancestor (nodo padre del valor que se está buscando)
       no se quiere que tenga un espacio, por lo que se asegura que si es igual a 2
       (penúltimo nodo) no se agregue. De igual forma, como el caso base está arriba
       tampoco llega al 1.
    */ 
    if (count_space != 2){
        aux << " ";
    }

    // Ves hacia donde tienes que recorrer y recorres hacia (left)
    if (val < value){
        left -> ancestors_recursion(aux, val);
    }
    // Ves hacia donde tienes que recorrer y recorres hacia (right)
    if (val > value) {
        right -> ancestors_recursion(aux, val);
    }
}

template <class T>
int TreeNode<T>::count_elements(int& count){
    // Recorres el árbol incrementando el contador hasta que no haya nada
    if (left != 0){
        left -> count_elements(count);
        count++;
    }
    if (right != 0){
        right -> count_elements(count);
        count++;
    }
    return count;
}

// Como es preorder lo junta antes de ir recorriendo
template <class T>
void TreeNode<T>::preorder(stringstream &aux) const {
    // Se imprime al principio
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}

	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

// Como es inorder lo junta a la mitad (entre left y right)
template <class T>
void TreeNode<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
    // Se imprime a la mitad
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

// Como es postorder lo junta después de recorrer (hojas)
template <class T>
void TreeNode<T>::postorder(stringstream &aux) const {
    // Si hay elemento llamas la recursión
	if (left != 0) {
		left->postorder(aux);
        aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
        aux << " ";
	}
    // Se imprime al final
    aux << value;
}

template <class T>
void TreeNode<T>::print_level(stringstream &aux, TreeNode<T>* root, int level, int total_elements, int& element_num){

    // Sacas el nivel del current node
    int level_num = 1;
    // Sacar el nivel del valor
    root -> whatlevelamI(value, level_num);

    // Si el nivel sacado, es igual al nivel del for loop entonces lo agregas
    if (level_num == level){
        aux << value;
        // Incrementas el número de elementos para saber en cual no poner espacio
        element_num++;

        // Si el número de elementos imprimidos es distinto al total poner un espacio
        if (total_elements != element_num){
            aux << " ";
        }
    }
    else {
        // Aseguras que exista left
        if (left != 0){
            // Llamas la recursión
            left -> print_level(aux, root, level, total_elements, element_num);
        }
        // Aseguras que exista right
        if (right != 0){
            // Llamas la recursión
            right -> print_level(aux, root, level, total_elements, element_num);
        }
    }
}

template <class T>
void TreeNode<T>::level_by_level(stringstream &aux, TreeNode<T>* root) {
    // Sacas el height del árbol para saber cuántos niveles hay que imprimir
    int height_num = 1;
    height(height_num, root);

    // Sacas el número de elementos para saber donde poner el espacio
    int elements = 1;
    root -> count_elements(elements);

    int element_num = 0;

    // Haces un for loop que corra las veces del height
    for (int count = 1; count <= height_num; count++){
        print_level(aux, root, count, elements, element_num);
    }
}

// Este es el árbol completo que tiene el apuntador a la raíz
template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
    // Constructor
	BST();

    // Funciones simples implementadas en clase
    bool empty() const;
	void add(T);

    // Funciones pedidas a implementar
    string visit();
    int height();
    string ancestors(T val);
    int whatlevelamI(T val);

    // Funciones distintas para imprimir el árbol
    string preorder() const;
	string inorder() const;
    string postorder() const;
    string level_by_level() const;
};

// Creas el arbol donde inicias la raíz a 0
template <class T>
BST<T>::BST() : root(0) {}

// Si la raíz es 0, el árbol está vacío
template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

// Función de agregar
template<class T>
void BST<T>::add(T val) {
	// Si el root está vacío y existe el árbol
    int count = 1;
	if (root != 0){
		// Buscas el objeto para ver si ya está el valor
		if (!root -> find(val, count)){
			// Si no, se agrega el valor.
			// Esto llama a la función de add de Node, (en este caso root)
			root -> add(val);
		}
	}
	// Si apenas empieza el árbol entonces creas el primer árbol
	else {
		root = new TreeNode<T>(val);
	}
}
// Funciones a implementar

template <class T>
string BST<T>::visit(){
    // Creas la variable en donde guardar los datos
    string preorder_text, inorder_text, postorder_text, level_by_level_text;

    // Guardas el texto llamando cada función
    preorder_text = preorder();
    inorder_text = inorder();
    postorder_text = postorder();
    level_by_level_text = level_by_level();

    // Creas la variable a regresar donde se suma todo
    string final;
    final = preorder_text + "\n" + inorder_text + "\n" + postorder_text + "\n" + level_by_level_text;
    return final;
}

template <class T>
int BST<T>::height(){
    // Iniciar la altura en 1 si existe raíz
    // Asegurar que exista un árbol
    int count = 1;
    if (root != 0){
        return root -> height(count, root);
    }
    // Si no regresar 0
    else {
        return 0;
    }
}

template <class T>
string BST<T>::ancestors(T val){
    stringstream aux;
    // Para que se imprima en cualquier caso
	aux << "[";
    if (root != 0){
        // Llamas a mandar la función auxiliar
        root -> ancestors_exist(aux, val);
    }
	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val){
    // Si no es nulo llamas al find whatlevelamI
    int count = 1;
    if (root != 0){
        return root -> whatlevelamI(val, count);
    }
    else {
        return 0;
    }
}

// Imprimir el árbol de distintas formas
template <class T>
string BST<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::postorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string BST<T>::level_by_level() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->level_by_level(aux, root);
	}
	aux << "]";
	return aux.str();
}

#endif /* BST_H_ */