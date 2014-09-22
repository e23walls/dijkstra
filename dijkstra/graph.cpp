//
//  graph.cpp
//  graphSearching
//
//  Created by Emily Jennyne Carroll Walls on 2014-04-27.
//  Copyright (c) 2014 Emily Walls. All rights reserved.
//

#include "graph.h"
#include <queue>
#include <stack>
#include <math.h>

// Vertex class implementation
Vertex::Vertex(std::string data)
{
    this->data = data;
    this->d_value = INFINITY;
    this->pi = NULL;
}
Vertex::Vertex(std::string data, std::vector<Vertex *> neighbours)
{
    this->data = data;
    this->neighbours = neighbours;
    marked = false;
    this->d_value = INFINITY;
    this->pi = NULL;
}
Vertex::~Vertex() {}
void Vertex::setData(std::string data)
{
    this->data = data;
}
std::string Vertex::getData()
{
    return this->data;
}
std::vector<Vertex *> Vertex::getNeighbours()
{
    return this->neighbours;
}
std::vector<double> Vertex::getWeights()
{
    return this->weights;
}
void Vertex::addNeighbour(Vertex * newNeighbour, double weight)
{
    neighbours.push_back(newNeighbour);
    weights.push_back(weight);
}
struct CompareVertices
{
    bool operator() (const Vertex &l, const Vertex &r) {return l.d_value > r.d_value;}
};

void joinVertices(Vertex * v1, Vertex * v2, double weight)
{
    v1->addNeighbour(v2, weight);
    v2->addNeighbour(v1, weight);
}

// Graph class implementation

Graph::Graph(Vertex * first)
{
    this->first = first;
}
Graph::~Graph()
{
    // need to free all memory somehow (add everything to array, and call delete on each one?)
    Vertex * curr = first;
    std::queue<Vertex *> q;
    std::vector<Vertex *> currNeigh;
    std::vector<Vertex *> temp;
    // add to queue, and print data at each
    curr->marked = true;
    while (curr)
    {
        temp.push_back(curr);
        curr->marked = true;
        currNeigh = curr->getNeighbours();
        for (int i = 0; i < currNeigh.size(); i++)
        {
            if (currNeigh[i]->marked == false)
            {
                q.push(currNeigh[i]);
                currNeigh[i]->marked = true;
            }
        }
        if (q.size())
        {
            curr = q.front();
            q.pop();
        }
        else
            curr = 0;
    }
    for (int i = 0; i < temp.size(); i++)
    {
        delete temp[i];
    }
}

void Graph::addVertex(Vertex * v)
{
    allVertices.push_back(v);
}
Vertex * Graph::findVertex(std::string data)
{
    Vertex * curr = first;
    Vertex * toReturn = 0;
    std::queue<Vertex *> q;
    std::vector<Vertex *> currNeigh;
    std::vector<Vertex *> temp;
    // add to queue, and print data at each
    curr->marked = true;
    while (curr)
    {
        temp.push_back(curr);
        curr->marked = true;
        if (curr->getData() == data)
            toReturn = curr;
        currNeigh = curr->getNeighbours();
        for (int i = 0; i < currNeigh.size(); i++)
        {
            if (currNeigh[i]->marked == false)
            {
                q.push(currNeigh[i]);
                currNeigh[i]->marked = true;
            }
        }
        if (q.size())
        {
            curr = q.front();
            q.pop();
        }
        else
            curr = 0;
    }
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i]->marked = false;
    }
    return toReturn;
}
void Graph::print() // print using breadth-first traversal
{
    Vertex * curr = first;
    std::queue<Vertex *> q;
    std::vector<Vertex *> currNeigh;
    std::vector<Vertex *> temp;
    // add to queue, and print data at each
    curr->marked = true;
    std::cout << curr->getData() << std::endl;
    while (curr)
    {
        temp.push_back(curr);
        curr->marked = true;
        currNeigh = curr->getNeighbours();
        for (int i = 0; i < currNeigh.size(); i++)
        {
            if (currNeigh[i]->marked == false)
            {
                q.push(currNeigh[i]);
                std::cout << currNeigh[i]->getData() << std::endl;
                currNeigh[i]->marked = true;
            }
        }
        if (q.size())
        {
            curr = q.front();
            q.pop();
        }
        else
            curr = 0;
    }
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i]->marked = false;
    }
}

void DFS(Vertex * v, std::stack<Vertex *> & s)
{
    Vertex * curr = v;
    std::vector<Vertex *> currNeigh;
    // add to queue, and print data at each
    curr->marked = true;
    std::cout << curr->getData() << std::endl;
    while (curr)
    {
        curr->marked = true;
        currNeigh = curr->getNeighbours();
        for (int i = 0; i < currNeigh.size(); i++)
        {
            if (currNeigh[i]->marked == false)
            {
                DFS(currNeigh[i], s);
            }
        }
        if (s.size())
        {
            curr = s.top();
            s.pop();
        }
        else
        {
            curr = 0;
        }
    }
}

// 'v' is a pointer to the last Vertex in the graph
void backTraceGraph(Vertex * v)
{
    Vertex * curr = v;
    while (curr)
    {
        std::cout << curr->getData() << std::endl;
        curr = curr->pi;
        
    }
}

void DFS(Vertex * const v, Vertex * last, std::stack<Vertex *> & s, std::vector<Vertex *> & solution)
{
    Vertex * curr = v;
    std::vector<Vertex *> currNeigh;
    // add to queue, and print data at each
    while (curr)
    {
        curr->marked = true;
        std::cout << curr->getData() << std::endl;
        solution.push_back(curr);
        curr->marked = true;
        currNeigh = curr->getNeighbours();
        for (int i = 0; i < currNeigh.size(); i++)
        {
            if (currNeigh[i]->marked == false)
            {
                DFS(currNeigh[i], last, s, solution);
            }
        }
        if (s.size())
        {
            curr = s.top();
            s.pop();
        }
        else
        {
            if (currNeigh.size() > 0 && solution[solution.size() - 1]->getData() != last->getData())
            {
                solution.pop_back();
            }
            curr = 0;
        }
    }
}
void Graph::topologicalSort()
{
    Vertex * curr = first;
    std::stack<Vertex *> s;
    DFS(curr, s);
    
    for (int i = 0; i < allVertices.size(); i++)
    {
        allVertices[i]->marked = false;
    }
}

Maze::Maze(Vertex * first) : Graph(first)
{}
Maze::~Maze()
{
}

void Maze::solve(Vertex * last)
{
    Vertex * curr = first;
    std::stack<Vertex *> s;
    std::vector<Vertex *> solution;
    DFS(curr, last, s, solution);
    curr = first;
    
    for (int i = 0; i < allVertices.size(); i++)
    {
        allVertices[i]->marked = false;
    }
    
    std::cout << "SOLUTION PATH:\n";
    for (int i = 0; i < solution.size(); i++)
    {
        std::cout << solution[i]->getData() << std::endl;
    }
}


