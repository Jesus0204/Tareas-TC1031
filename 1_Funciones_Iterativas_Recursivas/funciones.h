/*
 * funciones.h
 *
 *  Created on: 24/08/2023
 *      Author: Jesús Alejandro Cedillo Zertuche 
 *      A01705442
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones {
    public: 
        long sumaIterativa (int n);

        long sumaRecursiva (int n);

        long sumaDirecta (int n);
};

// O(n) lineal porque solo tiene un ciclo con incremento de 1
long Funciones :: sumaIterativa(int n){

    int count = 0;
    for (int i = 0; i <= n; i++){
        count = count + i;
    }
    return count;
}

// O(n) lineal
long Funciones :: sumaRecursiva(int n){

    if (n == 0){
        return 0;
    }
    else {
        return n + sumaRecursiva(n - 1);
    }
}

/* Se usa la fórmula matemática de inducción de (n(n+1)/2)
   Esta es la fórmula de una sumatoria sin usar ciclos ni recursión
   https://www.lasclasesdegonzalo.com/sumarnumeros 
*/
long Funciones :: sumaDirecta(int n){
    
    // La fórmula en código
    int sum = (n * (n + 1) / 2);
    return sum;
}

#endif /* FUNCIONES_H_ */