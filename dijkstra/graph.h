//
//  graph.h
//  graphSearching
//
//  Created by Emily Jennyne Carroll Walls on 2014-04-27.
//  Copyright (c) 2014 Emily Walls. All rights reserved.
//

#ifndef __graphSearching__graph__
#define __graphSearching__graph__

#include <iostream>
#include <deque>
#include <vector>
#include <stack>

class Vertex
{
public:
    Vertex(std::string data);
    Vertex(std::string data, std::vector<Vertex *> neighbours);
    ~Vertex();
    std::string getData();
    void setData(std::string data);
    std::vector<Vertex *> getNeighbours();
    bool marked;
    // Create a one-way edge
    void addNeighbour(Vertex * newNeighbour, double weight);
    std::vector<double> getWeights();
    
    double d_value;
    Vertex * pi;
    // Create a two-way edge
    friend void joinVertices(Vertex * v1, Vertex * v2, double weight); // no edge
private:
    std::string data;
    // weights[i] corresponds to weight of edge from this vertex
    // to the vertex neighbours[i]
    std::vector<Vertex *> neighbours;
    std::vector<double> weights;
};

void backTraceGraph(Vertex * v);

class Edge
{
public:
    Edge(Vertex * f, Vertex * t);
    ~Edge();
    Vertex * getFrom();
    Vertex * getTo();
private:
    Vertex * from; // allows for direction; edge goes from this From Vertex to the To one
    Vertex * to;
};

class Graph
{
public:
    Graph(Vertex * first); // a graph only requires a first node
    ~Graph();
    Vertex * findVertex(std::string data);
    void print();
    void addVertex(Vertex * v);
    void topologicalSort();
protected:
    Vertex * first;
    std::vector<Vertex *> allVertices;
private:
    friend void DFS(Vertex * v, std::stack<Vertex *> s);
    friend void DFS(Vertex * v, std::stack<Vertex *> s);
};

class Maze : public Graph
{
public:
    Maze(Vertex * first);
    ~Maze();
    void solve (Vertex * last);
private:
    friend void DFS(Vertex * v, std::stack<Vertex *> s, std::vector<Vertex *> solution);
};

#endif /* defined(__graphSearching__graph__) */
