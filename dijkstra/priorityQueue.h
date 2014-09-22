//
//  main.cpp
//  heapCreator
//
//  Created by Emily Jennyne Carroll Walls on 2014-04-26.
//
//  Specialized for 'Vertex' class. TODO: use templates
//

#include <iostream>
#include <math.h> // This includes the INFINITY macro
#include "graph.h"

// Rearrange a vector<Vertex *> to be in the right form

using namespace std;

bool isHeap(deque<Vertex *> & A, int index)
{
    if (2 * index + 1 < A.size())
    {
        if (A[2 * index + 1] < A[index])
            return true;
    }
    else if (2 * index + 2 < A.size())
    {
        if (A[2 * index + 1] < A[index] && A[2 * index + 2] > A[index])
            return true;
    }
    else if (index < A.size())
        return true;
    return false;
}

void printHeap(deque<Vertex *> & A)
{
    for (int i = 0; i < A.size(); i++)
    {
        if (fmod(log2(i + 1), 1) == 0 && i != 0)
            cout << endl;
        cout << A[i]->getData() << " ";
    }
    cout << endl << endl;
}
void altPrintHeap(deque<Vertex *> & A)
{
    for (int i = 0; i < A.size(); i++)
    {
        if (fmod(log2(i + 1), 1) == 0 && i != 0)
            cout << endl;
        cout << A[i]->getData() << ":" << A[i]->d_value << " ";
    }
    cout << endl << endl;
}
void fullPrintHeap(deque<Vertex *> & A)
{
    for (int i = 0; i < A.size(); i++)
    {
        if (fmod(log2(i + 1), 1) == 0 && i != 0)
            cout << endl;
        cout << A[i]->getData() << ":" << A[i]->d_value;
        if (A[i]->pi)
            cout <<  ":" << A[i]->pi->getData();
        else
            cout << ":";
        cout << " ";
    }
    cout << endl << endl;
}

void maxHeapify(deque<Vertex *> & A, int index)
{
    Vertex * temp = 0;
    int left = 0, right = 0;
    int largest = 0;
    
    // child = 2 * parent + 1 or child = 2 * parent + 2
    // (child - 1) / 2 (if child add) or (child - 2) / 2 (if child even)
    //    int parent = 0;
    
    // Left child is at 2 * index + 1; right is at 2 * index + 2
    // Continue loop till node has no children
    if (index <= A.size()/2)
    {
        largest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;
        
        if (left < A.size() and A[index]->d_value <= A[left]->d_value)
            largest = left;
        if (right < A.size() and A[left]->d_value <= A[right]->d_value)
            largest = right;
        if (index != largest)
        {
            if (A[index]->d_value < A[largest]->d_value)
            {
                temp = A[index];
                A[index] = A[largest];
                A[largest] = temp;
            }
            maxHeapify(A, largest);
        }
    }
}

void buildMaxHeap(deque<Vertex *> & A)
{
    for (int i = floor(A.size()/2); i >= 0; i--)
    {
        maxHeapify(A, i);
    }
}

void minHeapify(deque<Vertex *> & A, int index)
{
    Vertex * temp = 0;
    int left = 0, right = 0;
    int smallest = 0;
    
    // child = 2 * parent + 1 or child = 2 * parent + 2
    // (child - 1) / 2 (if child add) or (child - 2) / 2 (if child even)
    //    int parent = 0;
    
    // Left child is at 2 * index + 1; right is at 2 * index + 2
    // Continue loop till node has no children
    if (2 * index + 1 < A.size())
    {
        smallest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;
        
        if (left < A.size() and A[index]->d_value >= A[left]->d_value)
            smallest = left;
        if (right < A.size() and A[left]->d_value >= A[right]->d_value)
            smallest = right;
        if (index != smallest)
        {
            if (A[smallest]->d_value < A[index]->d_value)
            {
                // swap
                temp = A[index];
                A[index] = A[smallest];
                A[smallest] = temp;
            }
            minHeapify(A, smallest);
        }
    }
}
void buildMinHeap(deque<Vertex *> & A)
{
//    cout << "Starting at " << floor(A.size()/2) << endl;
    for (int i = floor(A.size()/2); i >= 0; i--)
    {
        minHeapify(A, i);
    }
}
