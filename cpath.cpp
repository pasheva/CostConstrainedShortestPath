#include<iostream>
#include "CPath.h"

using namespace std;

int main(int argc, char *argv[]){

    graph g;
    g.read_file(argv[1]);
    double budget = 3.0;
    CPath<double,double,int> myPath(g,budget);

    cout << "\nF*** THAT SHIT ASS NEIGHBOURS:\n\n";
    myPath.check();


    return 0;
}

