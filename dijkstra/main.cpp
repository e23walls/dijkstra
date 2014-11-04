//
//  main.cpp
//  dijkstra
//
//  Created by Emily Jennyne Carroll Walls on 2014-05-18.
//  Copyright (c) 2014 Emily Walls. All rights reserved.
//

#include <iostream>
#include "priorityQueue.h"

//#define DEBUG

void backTrace(Vertex * v);
struct CompareVertices;

using namespace std;

#ifdef DEBUG
deque<Vertex *> dijkstra (deque<Vertex *> & graph, Vertex * start, Vertex * destination)
#else
void dijkstra (deque<Vertex *> & G, Vertex * start, Vertex * destination)
#endif
{
#ifdef DEBUG
    deque<Vertex *> G = graph;
#endif
    // Get everything ready for algorithm:
    start->d_value = 0.0;
    // Every other d_value is initialized to infinity,
    // so we can ignore them.
    
    buildMinHeap(G);
    Vertex * current = NULL;
    Vertex * neighbour = NULL;
    double newWeight = 0;
    while (G.size())
    {
        current = G.front();
        G.pop_front();
        for (int i = 0; i < current->getNeighbours().size(); i++)
        {
            neighbour = current->getNeighbours()[i];
            // Relax edge
            newWeight = current->getWeights()[i] + current->d_value;
            if (newWeight < neighbour->d_value)
            {
                neighbour->d_value = newWeight;
                neighbour->pi = current;
                buildMinHeap(G);
            }
        }
    }
#ifdef DEBUG
    // This isn't really necessary...
    buildMinHeap(graph);
    return graph;
#endif
}


int main(int argc, const char * argv[])
{
    Vertex * alice = new Vertex("Alice");
    Vertex * bob = new Vertex("Bob");
    Vertex * claire = new Vertex("Claire");
    Vertex * dennis = new Vertex("Dennis");
    Vertex * ester = new Vertex("Ester");
    Vertex * frank = new Vertex("Frank");
    Vertex * georgina = new Vertex("Georgina");
    
    deque<Vertex *> graph;
    
    graph.push_back(alice);
    graph.push_back(bob);
    graph.push_back(claire);
    graph.push_back(dennis);
    graph.push_back(ester);
    graph.push_back(frank);
    graph.push_back(georgina);
    
    joinVertices(alice, bob, 5.0);
    joinVertices(alice, claire, 6.0);
    joinVertices(claire, frank, 4.0);
    joinVertices(alice, frank, 4.0);
    joinVertices(ester, claire, 5.0);
    joinVertices(dennis, georgina, 8.0);
    joinVertices(dennis, claire, 6.0);
    joinVertices(frank, georgina, 5.0);
    joinVertices(ester, dennis, 5.5);
    
    Vertex * start = bob;
    Vertex * end = dennis;
    
    // How many people must (start) meet to get to (end)?
    dijkstra(graph, start, end);
    cout << "Shortest path from '"<< start->getData() << "' to '" << end->getData() << "' has length of " << end->d_value << ".\n";
    backTraceGraph(end);
    
    delete alice;
    delete bob;
    delete claire;
    delete dennis;
    delete ester;
    delete frank;
    delete georgina;
    
    return 0;
}

