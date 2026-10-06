#pragma once
#include <iostream>
using namespace std;

// Structural node for Circular Singly Linked List
struct Node {
    int data;
    Node* next;
};

bool isEmpty(Node* head);
void pushHead(Node*& head, int value, int& ptrMoves);
void pushTail(Node*& head, int value, int& ptrMoves);
int getLength(Node* head);
void printList(Node* head);
void freeList(Node*& head);
int taskA(Node*& head, int E);  // Remove first & last occurrence of E
int taskB(Node*& head);         // Move maximum element to head
int taskC(Node* head, int& nodeCount); // Recursively count nodes
