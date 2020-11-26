#include<iostream>
#include "CPath.h"

using namespace std;

int main(int argc, char *argv[]){


    graph g;

    if(argc != 5) {
        std::cout << "usage:  ./cpath <file> <s> <d> <budget>\n";
        return 0;
    }else {
        if(!g.read_file(argv[1])){ // Reading file
            std::cout << "could not open file '" << argv[1] << "'\n";
            return 0;
        }
    }

    double budget = stoi(argv[4]);
    string src = argv[2];
    string dst = argv[3];

    CPath<double,double,string> myPath(g,budget);

    myPath.findPaths(src);
    // PARETO TRADEOFF CURVE | NON-DOMINATED PATHS
    myPath.checkP(dst);
    // COST-FEASIBLE AND FASTEST PAIR(COST, TIME) && ACTUAL PATH
    myPath.feasiblePath(src,dst);


    cout << endl;
    return 0;
}

