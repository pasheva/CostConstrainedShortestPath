#pragma once
#ifndef CPATH_H
#define CPATH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include "Graph.h"

using namespace std;



template <typename CostT, typename TimeT,  typename VertexT>
class CPath{


protected:
    struct Signature{
        VertexT vertex;
        VertexT pred = {};
        CostT cost;
        TimeT time;
    };

private:

    CostT budget;
    graph G;

    unordered_map<VertexT, vector<Signature>> P;
    unordered_map<string, unordered_map<string, pair<double,double>>> layout;


public:
    CPath();
    CPath<CostT, TimeT, VertexT>(graph& G, CostT& budget);
    bool operator() (Signature const& p1, Signature const &p2);
    void findPaths(VertexT sourceV);
    void feasiblePath(VertexT start, VertexT dest);
    void checkP(VertexT dest);
};



/**
 * Default constructor needed for the operator overloading.
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 */
template<typename CostT, typename TimeT, typename VertexT>
CPath<CostT, TimeT, VertexT>::CPath() {}

/**
 *
 * Constructor used to create the object with
 * which are working in the cpath.cpp file.
 *
 * A function to layoutGraph() has been added to Graph.h class.
 * This function is helping us store the graph as hastable of vertecies and signatures.
 *
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 * @param G Passing already created graph.
 * @param budget Amount based on user input.
 */
template<typename CostT, typename TimeT, typename VertexT>
CPath<CostT, TimeT, VertexT>::CPath(graph& G, CostT& budget) {
    this->budget = budget;
    this->G = G;
    this->layout = G.layoutGraph();
}

/**
 *
 * Overloading the () operator in order to use it for the
 * min-heap priority queue.
 * Order of comparisons: 1. Cost 2. Time 3. Vertex
 *
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 * @param p1
 * @param p2
 * @return
 */
template<typename CostT, typename TimeT, typename VertexT>
bool CPath<CostT, TimeT, VertexT>::operator()(const CPath::Signature &p1, const CPath::Signature &p2) {
    {
        if (p1.cost != p2.cost)
        {
            return p1.cost > p2.cost;
        }
        else
        {
            if (p1.time != p2.time)
            {
                return p1.time > p2.time;
            }
            else
            {
                return p1.vertex > p2.vertex;
            }
        }
    }
}

/**
 *
 * Finding the paths based on the algorithm
 * and queueing them to P[Vertex] in the Pareto
 * method. [cost -> increasing, time -> decreasing]
 *
 * We result in a complete non-dominated paths for each vertex.
 *
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 * @param sourceV Soruce vertex based on user input.
 */
template<typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::findPaths(VertexT sourceV) {


    priority_queue<Signature, vector<Signature>, CPath<CostT,TimeT,VertexT>> pq;

    Signature t;
    t.pred = {};
    t.cost = 0;
    t.time = 0;
    t.vertex = sourceV;
    pq.emplace(t);

    while (!pq.empty()){
         Signature currNode = pq.top();
         pq.pop();
         VertexT currVertex = currNode.vertex;
         CostT currCost = currNode.cost;
         TimeT currTime = currNode.time;

        auto pathsForV = P.find(currVertex);
        if( pathsForV == P.end()){  P.emplace(currVertex, vector<Signature>());}
        pathsForV = P.find(currVertex);

        if(currCost > this->budget) { continue; }
        else if(pathsForV->second.empty()){ pathsForV->second.push_back(currNode); }
        else if (currTime >= pathsForV->second.back().time){ continue; }
        else{ pathsForV->second.push_back(currNode); }

        //Populate
        auto temp = layout.find(currVertex);
        if(!(temp == layout.end())){
            for(auto &V2 : temp->second){
                // Neighbour, Cost, Time
                Signature tempSig;
                tempSig.pred = currVertex;
                tempSig.vertex = V2.first;
                tempSig.cost = V2.second.first + currCost;
                tempSig.time = V2.second.second + currTime;
                pq.emplace(tempSig);
            }
        }
    }
}



/**
 *
 * We are analyzing the P[] and outputing the
 * non-dominated signatures of the destination vertex.
 *
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 * @param dest Based on user input.
 */
template<typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::checkP(VertexT dest) {


        cout << "PARETO TRADEOFF CURVE | NON-DOMINATED PATHS" << endl;
        cout << "-------------------------------------------" << endl;

        auto V = P.find(dest);
        if(V == P.end()){
            cout << "PATH NOT FEASIBLE!\n " << endl;
            return;
        }
        cout << "(Cost,Time)" << endl;
        for(auto &V2 : V->second){
            cout << "(" << V2.cost << "  ,  " << V2.time << ")\n";
        }
        cout << endl;

}


/**
 *
 * Grabbing our destination tail from the P[dest].
 * This is giving us the most optimal path in terms of
 * most expensive and least time.
 *
 * From then on we are storing the predecessors for each of the signatures
 * and we are utilizing that to walk back P[] in order to get the full path.
 *
 * Also, we are considering the cost and time from the original edges and substracting
 * from the current, thus, comparing to the predesessor to find which of the P[predecessors]
 * entries is the correct one.
 *
 * If we don't reach our destination and some of the vertecies do not exist as we walk back
 * then the path is not found.
 *
 * @tparam CostT
 * @tparam TimeT
 * @tparam VertexT
 * @param start
 * @param dest
 */
template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::feasiblePath(VertexT start, VertexT dest) {

    cout << "COST-FEASIBLE AND FASTEST PAIR(COST, TIME): " << endl;
    cout << "------------------------------------------" << endl;
    stack<VertexT> path;

    auto pathsForV = P.find(dest);
    if(pathsForV == P.end()){
        cout << "PATH NOT FEASIBLE! " << endl;
        return;
    }
    vector<Signature> t = pathsForV->second;
    VertexT currV = dest;
    Signature sig = t.back();
    CostT currCost = sig.cost;
    TimeT currTime = sig.time;

    cout << "(" << currCost << " , " << currTime << ")" << endl;

    CostT orgCost;
    TimeT orgTime;
    VertexT pred;
    path.push(currV);

    while (currV != start ) {
        pred = sig.pred;

        auto i = layout.find(pred);
        if (i != layout.end()) {
            auto b = i->second.find(currV);
            if (b != i->second.end()) {
                orgCost = b->second.first;
                orgTime = b->second.second;
            }else{
                cout << "\nPATH NOT FEASIBLE!" << endl;
                return; };
        }else{
            cout << "\nPATH NOT FEASIBLE! " << endl;
            return; }

        pathsForV = P.find(pred);
        t = pathsForV->second;
        for (const auto &n : t) {
            if (((currCost - orgCost) == n.cost) && (currTime - orgTime == n.time)) {
                sig = n;
                currCost = n.cost;
                currTime = n.time;
                currV = n.vertex;
                path.push(currV);
            }
        }
    }
    cout << "\nACTUAL PATH: " << endl;
    cout << "------------------------" << endl;
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
}

#endif
