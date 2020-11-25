#pragma once
#ifndef CPATH_H
#define CPATH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Graph.h"


using namespace std;


template <typename CostT, typename TimeT,  typename VertexT>
class CPath{

private:
    struct Signature{
        VertexT vertex;
        CostT cost;
        TimeT time;
    };

    CostT budget;
    graph G;

    //Hash of Vectors
    unordered_map<VertexT, vector<Signature>> P;
    unordered_map<string, unordered_map<string, pair<double,double>>> layout;
    //minheap pq;

public:
    CPath<CostT, TimeT, VertexT>(graph& G, CostT& budget);
    void findPaths();
    void check();


};

template<typename CostT, typename TimeT, typename VertexT>
CPath<CostT, TimeT, VertexT>::CPath(graph& G, CostT& budget) {
    this->budget = budget;
    this->G = G;
    this->layout = G.layoutGraph();
}

template<typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::findPaths() {
    // while (pq.empty!){
        //  currNode = pq.top();
        //  pq.pop();
        // currVertex =
        // currCost =
        // currTime =
        // size = P.at(currVertex).size()-1

        //if currCost > this.budget{ fuckoff;}

        //if(!P.empty()){
        //  P.at(currVertex).push_back(currNode);
        //}
        //else if (currTime >= P[currVertex][size][currTime]){
        //      continue;
        // }
        //else{
        //  add signature of curr to vectorList[cver]
        // }
        // populate the minq with neighbors() and ccost, ctime

        ;
}

template<typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::check() {
    for(auto& V: this->layout){
        // forVertex
        cout << V.first << " : ";
        for(auto &V2 : V.second){
            // Neighbour Vertex , Cost , Time
            cout << "(" << V2.first << "," << V2.second.first << "," << V2.second.second << ")";
        }
        cout << endl;
    }
}


#endif

