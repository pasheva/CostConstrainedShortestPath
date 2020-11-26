#include<iostream>
#include "CPath.h"

using namespace std;

int main(int argc, char *argv[]){


    // TODO: “cpath <file> <s> <d> <budget>”.

    graph g;
    g.read_file(argv[1]); // Reading file
    double budget = 10;
    CPath<double,double,string> myPath(g,budget);

    cout << "\nF*** THAT SHIT ASS NEIGHBOURS:\n\n";
    myPath.findPaths("0");
    cout << endl;
    myPath.check();
    return 0;
}

