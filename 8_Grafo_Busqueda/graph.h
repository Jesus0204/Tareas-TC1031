/*
 * graph.h
 *
 *  Created on: 14/11/2023
 *      Author: Jesús Alejandro Cedillo Zertuche
 */

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;

public:
		// Constructores
		Graph(int);
		Graph();

		// Funciones para cargar conexiones a lista y matrices
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
		void addEdgeAdjMatrix(int, int);
		void addEdgeAdjList(int, int);

		// Funciones de busqueda
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int> >&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int> >&);

		// Prints para funciones de busqueda
		string print_visited(list<int>);
		string print_path(vector<vector<int> >&,int ,int);

		// Prints de las conexiones del grafo
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();

		// Funciones auxilares
		bool contains(list<int>, int);
		void sortAdjList();
};

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	// Creas el vector
	adjList = new vector<int>[nodes];
	// Creas la matrix e inicializas todo a 0
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}


void Graph::loadGraphMat(string data, int node_tam, int edge_tam){
	// Creas la matriz
	adjMatrix = new int [node_tam * edge_tam];	

	// Le indicas a la clase cuantos nodos hay
	nodes = node_tam;

	// Inicializas todos los indices de la matriz en 0
	for (int i = 0; i < node_tam * edge_tam; i++)
		adjMatrix[i] = 0;	
	
	// Variables temporales a 0
	int u, v, i = 0;
	// Mientras el string de data siga teniendo chars
	while (i < data.size()) {
		// u lo haces int
		u = (int)data[i+1] - 48;			
		// Igual v
		v = (int)data[i+3] - 48;		
		// A i la sumas 6 para que entre a la siguiente conexión
		i = i + 6;
		// Llamas a mandar la función que agrega ese edge
		addEdgeAdjMatrix(u,v);
	}
}

void Graph :: loadGraphList(string data, int node_tam){
	// Creas el vector del tamano de los nodos
	adjList = new vector<int>[node_tam];
	// Le indicas a la clase cuantos nodos hay
	nodes = node_tam;
	// Variables temporales a 0
	int u, v, i = 0;
	// Mientras el string de data siga teniendo chars
	while (i < data.size()) {
			// u lo haces int
			u = (int)data[i+1] - 48;
			// Igual v
			v = (int)data[i+3] - 48;
			// A i la sumas 6 para que entre a la siguiente conexión
			i = i + 6;
			// Llamas a mandar la función que agrega ese edge
			addEdgeAdjList(u,v);
	}
	// Se hace el sort para la impresión
	sortAdjList();
}

void Graph::addEdgeAdjMatrix(int u, int v){
	// Usando la formula le agregas la conexión
	adjMatrix[u*nodes+v] = 1;
	// Haces lo mismo al revés para la simetría
	adjMatrix[v*nodes+u] = 1;
	// Agregas uno al contador de edges de matrix
	edgesMat++;
}

void Graph :: addEdgeAdjList(int u, int v){
	// Al nodo u le agregas la conexión de v
	adjList[u].push_back(v);
	// Al nodo v le agregas la conexión de u
	adjList[v].push_back(u);
	// Agregas uno al contador de edges de list
	edgesList++;
}

string Graph :: DFS(int start, int goal){
	// Creas el stack para el DFS
	stack <int> st;
	// Creas la lista de los nodos que fueron visitados
	list <int> visited;
	/* Creas la matriz de paths donde tiene una fila por nodo, y una columna con un -1
	 * Así paths es una matriz donde se guardan el camino que toma
	 */
	vector <vector<int> > paths(nodes, vector <int> (1, -1));
	// Agregas al stack el nodo con el cual comenzar
	st.push(start);
	// Llamar la función que hace la recursión y guardar lo que regresa en un string
	string ans = depthHelper(start, goal, st, visited, paths);
	// Imprimir el path que tomó 
	ans = ans + print_path(paths, start, goal);
	// Regresar ese string
	return ans;
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int> > &paths){
	// Si encontraste el nodo que se buscaba
	if (current == goal){
		return print_visited(visited);
	}
	// Si el stack ya no tiene nada se recorrió todo el grafo
	else if (st.empty()){
		return " node not found";
	}
	// Si todavía quedan elementos
	else {
		// Sacar el nodo actual del stack con top
		current = st.top();
		// Borrarlo del stack al elemento
		st.pop();
		// Agregar a la lista de visitado que ya visitaste el nodo
		visited.push_back(current);
		// Recorre la lista de conexiones de current
		for (int i = 0; i < adjList[current].size(); i++){
			// Si el nodo en la lista de conexiones no ha sido visitado
			if (!contains(visited, adjList[current][i])){
				// Agregas ese nodo al stack para que sea el siguiente visitado (en la siguiente iteración)
				st.push(adjList[current][i]);
				/* Aquí es como tener una lista con el nodo, y quien es su padre. De esta forma
				 * tienes al nodo, y el padre, y así se puede llegar del start al goal
				 */
				paths[adjList[current][i]][0] = current;
			}
		}
		// Llamas a la recursión con el nuevo current
		return depthHelper(current, goal, st, visited, paths);
	}
}

string Graph :: BFS(int start, int goal){
	// Creas el queue para el BFS
	queue <int> qu;
	// Creas la lista de los nodos que fueron visitados
	list <int> visited;
	// Crear la matriz de los paths para guardar el path que tomo con el número de nodos como fila
	vector <vector<int> > paths(nodes, vector <int> (1, -1));
	// Agregas al queue el nodo con el cual comenzar
	qu.push(start);
	// Llamar la función que hace la recursión y guardar lo que regresa en un string
	string ans = breadthHelper(start, goal, qu, visited, paths);
	// Imprimir el path que tomó 
	ans = ans + print_path(paths, start, goal);
	// Regresar ese string
	return ans;
}

string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int> > &paths){
	// Si encontraste el nodo que se buscaba
	if (current == goal){
		return print_visited(visited);
	}
	// Si el stack ya no tiene nada se recorrió todo el grafo
	else if (qu.empty()){
		return " node not found";
	}
	// Si todavía quedan elementos
	else {
		// Sacar el nodo actual del queue con front
		current = qu.front();
		// Borrarlo del queue al elemento
		qu.pop();
		// Agregar a la lista de visitado que ya visitaste el nodo
		visited.push_back(current);
		// Recorre la lista de conexiones de current
		for (int i = 0; i < adjList[current].size(); i++){
			// Si el nodo en la lista de conexiones no ha sido visitado
			if (!contains(visited, adjList[current][i])){
				// Agregas ese nodo al queue para que sea agregado a la fila y se visite cuando se tenga que visitar
				qu.push(adjList[current][i]);
				/* Aquí es como tener una lista con el nodo, y quien es su padre. De esta forma
				 * tienes al nodo, y el padre, y así se puede llegar del start al goal
				 * Ya que se encontró el nodo, te vas para atrás y funciona (que es lo que hace print path). Por eso se usa la misma lista
				 */
				// Solo actualizo la lista cuando no se tenga un valor. Si si existe, entonces no se cambia para que sea el más corto
				if (paths[adjList[current][i]][0] == -1){
					paths[adjList[current][i]][0] = current;
				}
			}
		}
		// Llamas a la recursión con el nuevo current
		return breadthHelper(current, goal, qu, visited, paths);
	}
}

// La función que imprime los nodos que visitó
string Graph::print_visited(list<int> q){
	// Creas el stringstream
	stringstream aux;
	aux << "visited: ";
	// Recorrer la lista
	while (!q.empty()){
		// Agregar al string el frente de la lista
		aux << q.front() << " ";
		// Borrarlo de la lista hasta que quede vacío
		q.pop_front();
  	}
	// Regresar el stringstream
	return aux.str();
}

// Algoritmo que imprime el path que tomo 
string Graph::print_path(vector<vector <int> > &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    	node = path[node][0];
 	}
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
 	}
	return aux.str();
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

// Sort del list
void Graph::sortAdjList(){
	// Se le hace la función del sort 
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(), adjList[i].end());
}

// Checa si la lista contiene al nodo
bool Graph::contains(list<int> ls, int node){
	// Creas un iterador
	list<int>::iterator it;
	// Usas la función de find para ver si existe el elemento
	it = find(ls.begin(), ls.end(), node);
	// Si el iterador no está vacío entonces regresa true
	if(it != ls.end())
		return true;
	// Si no es falso
	else
		return false;
}

#endif /* Graph_H_ */
