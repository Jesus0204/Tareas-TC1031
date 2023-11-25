/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*/

#include <iostream>
#include <cstring>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {

    Graph star;
    string star_input = "(0,1) (0,2) (0,3) (0,4) (1,2) (2,5) (4,6) (4,7) (5,6) (5,7) (6,7)";

    string star_ans, star_ans_2;

    star.loadGraphList(star_input, 18);
    star.loadGraphMat(star_input, 18, 18);

    cout << star.DFS(0,5) << endl;

    cout << star.BFS(0,5) << endl;

}