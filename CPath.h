#pragma once
#ifndef CPATH_H
#define CPATH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Graph.h"

using namespace std;

template <typename CostT, typename TimeT, typename VertexT>
class CPath
{

protected:
    struct Signature
    {
        VertexT vertex;
        VertexT pred = {};
        CostT cost;
        TimeT time;
    };

private:
    CostT budget;
    graph G;

    //Hash of Vectors
    unordered_map<VertexT, vector<Signature>> P;
    unordered_map<string, unordered_map<string, pair<double, double>>> layout;

public:
    CPath();
    CPath<CostT, TimeT, VertexT>(graph &G, CostT &budget);
    void findPaths(VertexT sourceV);
    bool operator()(Signature const &p1, Signature const &p2);
    void check();
    void checkPQ(priority_queue<Signature, vector<Signature>, CPath<CostT, TimeT, VertexT>> pq);
    void feasiblePath(VertexT start, VertexT dest);
    void test();
    void checkP();
};

template <typename CostT, typename TimeT, typename VertexT>
CPath<CostT, TimeT, VertexT>::CPath() {}

template <typename CostT, typename TimeT, typename VertexT>
CPath<CostT, TimeT, VertexT>::CPath(graph &G, CostT &budget)
{
    this->budget = budget;
    this->G = G;
    this->layout = G.layoutGraph();
}

template <typename CostT, typename TimeT, typename VertexT>
bool CPath<CostT, TimeT, VertexT>::operator()(const CPath::Signature &p1, const CPath::Signature &p2)
{
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

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::findPaths(VertexT sourceV)
{

    priority_queue<Signature, vector<Signature>, CPath<CostT, TimeT, VertexT>> pq;

    Signature t;
    t.cost = 0;
    t.time = 0;
    t.vertex = sourceV;
    pq.emplace(t);

    while (!pq.empty())
    {
        Signature currNode = pq.top();
        pq.pop();
        VertexT currVertex = currNode.vertex;
        CostT currCost = currNode.cost;
        TimeT currTime = currNode.time;

        auto pathsForV = P.find(currVertex);
        if (pathsForV == P.end())
        {
            P.emplace(currVertex, vector<Signature>());
        }
        pathsForV = P.find(currVertex);

        if (currCost > this->budget)
        {
            continue;
        }
        else if (pathsForV->second.empty())
        {
            pathsForV->second.push_back(currNode);
        }
        else if (currTime >= pathsForV->second.back().time)
        {
            continue;
        }
        else
        {
            pathsForV->second.push_back(currNode);
        }

        //Populate
        auto temp = layout.find(currVertex);
        if (!(temp == layout.end()))
        {
            for (auto &V2 : temp->second)
            {
                // Neighbour, Cost, Time
                Signature temp2;
                temp2.pred = currVertex;
                temp2.vertex = V2.first;
                temp2.cost = V2.second.first + currCost;
                temp2.time = V2.second.second + currTime;
                pq.emplace(temp2);
            }
        }
    }

    checkP();
    cout << endl;
    feasiblePath();
}

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::checkPQ(priority_queue<Signature, vector<Signature>, CPath<CostT, TimeT, VertexT>> pq)
{
    while (!pq.empty())
    {
        auto t = pq.top();

        pq.pop();

        cout << " (Neighbour: "
             << t.vertex
             << " Cost "
             << t.cost
             << " Time "
             << t.time << ") ";
    }
    cout << endl;
}

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::check()
{
    for (auto &V : this->layout)
    {
        // forVertex
        cout << V.first << " : ";
        for (auto &V2 : V.second)
        {
            // Neighbour Vertex , Cost , Time
            cout << "(" << V2.first << "," << V2.second.first << "," << V2.second.second << ")";
        }
        cout << endl;
    }
}

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::test()
{

    vector<Signature> test;
    Signature t;
    t.cost = 0;
    t.time = 0;
    t.vertex = '0';
    test.push_back(t);

    // sig t;
    t.cost = 2;
    t.time = 4;
    t.vertex = '1';
    test.push_back(t);

    // sig t;
    t.cost = 4;
    t.time = 2;
    t.vertex = '4';
    test.push_back(t);

    // sig t;
    t.cost = 4;
    t.time = 5;
    t.vertex = '0';
    test.push_back(t);

    // sig t;
    t.cost = 5;
    t.time = 6;
    t.vertex = '2';
    test.push_back(t);

    // sig t;
    t.cost = 6;
    t.time = 5;
    t.vertex = '5';
    test.push_back(t);

    // sig t;
    t.cost = 3;
    t.time = 9;
    t.vertex = '4';
    test.push_back(t);

    t.cost = 10;
    t.time = 3;
    t.vertex = '5';
    test.push_back(t);

    // sig t;
    t.cost = 10;
    t.time = 3;
    t.vertex = '1';
    test.push_back(t);

    // sig t;
    t.cost = 9;
    t.time = 3;
    t.vertex = '5';
    test.push_back(t);

    // sig t;
    t.cost = 7;
    t.time = 9;
    t.vertex = '6';
    test.push_back(t);

    // sig t;
    t.cost = 10;
    t.time = 6;
    t.vertex = '6';
    test.push_back(t);

    // sig t;
    t.cost = 15;
    t.time = 4;
    t.vertex = '2';
    test.push_back(t);

    // sig t;
    t.cost = 13;
    t.time = 4;
    t.vertex = '6';
    test.push_back(t);

    // sig t;
    t.cost = 12;
    t.time = 4;
    t.vertex = '3';
    test.push_back(t);

    // sig t;
    t.cost = 13;
    t.time = 5;
    t.vertex = '2';
    test.push_back(t);

    priority_queue<Signature, vector<Signature>, CPath<CostT, TimeT, VertexT>> pq;

    for (auto el : test)
    {

        pq.push(el);

        cout << "( " << el.cost << "," << el.time << " ) : " << el.vertex << "\n";
    }

    while (!pq.empty())
    {
        auto tlol = pq.top();

        pq.pop();

        cout << "Current val:\t(" << tlol.cost << "," << tlol.time << ") : " << tlol.vertex << endl;
    }
}

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::checkP()
{
    for (auto &V : this->P)
    {
        // forVertex
        cout << V.first << " : ";
        for (auto &V2 : V.second)
        {
            // Vertex , Cost , Time
            cout << "( " << V2.pred << "," << V2.cost << "," << V2.time << ")";
        }
        cout << endl;
    }
}

template <typename CostT, typename TimeT, typename VertexT>
void CPath<CostT, TimeT, VertexT>::feasiblePath(VertexT start, VertexT dest)
{

    // TODO: CHECK FOR FOR COST AND TIME BASED ON THE ORIGINAL EDGE (SUBSTRACTION)

    auto pathsForV = P.find("6");
    // auto pathsForV = P.find(dest);
    vector<Signature> t = pathsForV->second;
    VertexT currV = "6";
    Signature sig = t.back();
    CostT currCost = sig.cost;
    TimeT currTime = sig.time;

    CostT orgCost;
    TimeT orgTime;
    VertexT pred;
    cout << currV << " ";

    // while (currV != start){
    while (currV != "0")
    {
        pred = sig.pred;

        auto i = layout.find(pred);
        if (i != layout.end())
        {
            auto b = i->second.find(currV);
            if (b != layout.end())
            {
                orgCost = b->second.first;
                orgTime = b->second.second;
            }
        }

        pathsForV = P.find(pred);
        t = pathsForV->second;
        for (const auto &n : t)
        {
            if (((currCost - orgCost) == n.cost) && (currTime - orgTime == n.time))
            {
                sig = n;
                currCost = n.cost;
                currTime = n.time;
                currV = n.vertex;
                cout << currV << " ";
            }
        }
        // cout << currV << " ";
    }
}

#endif
